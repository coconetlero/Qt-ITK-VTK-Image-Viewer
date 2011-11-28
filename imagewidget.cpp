/* 
 * File:   imagewidget.cpp
 * Author: zian fanti
 * 
 * Created on 19 de septiembre de 2011, 19:34
 */
#include "QVBoxLayout"

#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageLuminance.h>

#include <vtkImageFlip.h>

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkCastImageFilter.h>
#include <itkMedianImageFilter.h>
#include <itkGradientAnisotropicDiffusionImageFilter.h>
#include <itkVectorGradientAnisotropicDiffusionImageFilter.h>

#include <vtkInteractorStyleImage.h>

#include "imagewidget.h"
#include "medianFilterDialog.h"
#include "GADFilterDialog.h"

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{

	this->setAttribute(Qt::WA_DeleteOnClose);

	qvtkWidget = new QVTKWidget(this);
	//    qvtkWidget->resize(640, 480);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	layout->addWidget(qvtkWidget);
	this->setLayout(layout);


	// Create image actor
	actor = vtkSmartPointer<vtkImageActor>::New();

	// A renderer and render window
	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

}

ImageWidget::~ImageWidget()
{
	renderWindow->Finalize();
	qvtkWidget = NULL;
	itkImage = NULL;
	vtkImage = NULL;
}

void ImageWidget::open()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    
	if (!fileName.isEmpty()) {

		// Obtain image information
		this->setImageProperties(fileName.toAscii().data(), true);

		// set itk image depending on the image type 
		// if image type is grayscale
		if (imageType.compare("scalar") == 0) {
			// read the image
			typedef itk::ImageFileReader <ImageType> ReaderType;
			ReaderType::Pointer reader = ReaderType::New();
			reader->SetFileName(fileName.toAscii().data());
			reader->Update();

			// set the image data provided bye the reader
			itkImage = reader->GetOutput();

		} else {
			// if the image is RGB
			typedef itk::ImageFileReader <RGBImageType> ReaderType;
			ReaderType::Pointer reader = ReaderType::New();
			reader->SetFileName(fileName.toAscii().data());
			reader->Update();

			// set the image data provided bye the reader
			rgbItkImage = reader->GetOutput();
		}

		// reads a vtkImage for display purposes
		vtkSmartPointer <vtkImageReader2Factory> readerFactory =
			vtkSmartPointer <vtkImageReader2Factory>::New();
		vtkSmartPointer <vtkImageReader2> reader =
			readerFactory->CreateImageReader2(fileName.toAscii().data());

		reader->SetFileName(fileName.toAscii().data());
		reader->Update();

		vtkImage = reader->GetOutput();

		this->isFliped = true;
		this->displayImage(vtkImage);


		readerFactory = NULL;
		reader = NULL;

	} else {
		QErrorMessage errorMessage;
		errorMessage.showMessage("No file specified for loading");
		errorMessage.exec();
		return;
	}
}

void ImageWidget::openWithITK()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    
	if (!fileName.isEmpty()) {

		// read the image
		typedef itk::ImageFileReader <ImageType> ReaderType;
		ReaderType::Pointer reader = ReaderType::New();
		reader->SetFileName(fileName.toAscii().data());
		reader->Update();

		// set the image data provided bye the reader
		itkImage = reader->GetOutput();

		// setup and connect itk with vtk
		vtkConnectorType::Pointer connector = vtkConnectorType::New();
		connector->GetExporter()->SetInput(itkImage);
		connector->GetImporter()->Update();

		// flip image in Y axis				
		vtkSmartPointer<vtkImageFlip> flipYFilter = vtkSmartPointer<vtkImageFlip>::New();
		flipYFilter->SetFilteredAxis(1); // flip Y axis
		flipYFilter->SetInput(connector->GetImporter()->GetOutput());
		flipYFilter->Update();

		// create vtk image
		vtkImage = vtkSmartPointer<vtkImageData>::New();
		vtkImage->DeepCopy(flipYFilter->GetOutput());
		vtkImage->SetScalarTypeToUnsignedChar();
		vtkImage->Update();

		this->displayImage(vtkImage);

		reader = NULL;
		flipYFilter = NULL;
		connector = NULL;
	}
}

void ImageWidget::medianFilter()
{
	// create and show the median filter dialog 
	MedianFilterDialog filterDialog(this);
    
    // if the user don't cancel the action
	if (filterDialog.exec()) {
		// get selected value from dialog
		int intensity = filterDialog.spinBox->value();

		// if the itkImage is not loaded, then vtkImage is converted to itkImage 
		if (itkImage.IsNull()) {
			this->setITKImageFromVTK();
		}

		// setup the itk median filter
		typedef itk::MedianImageFilter<ImageType, ImageType> FilterType;

		FilterType::Pointer filter = FilterType::New();
		FilterType::InputSizeType radius;
		radius.Fill(intensity);

		filter->SetRadius(radius);
		filter->SetInput(itkImage);
        filter->Update();
        
        
		// setup and connect itk with vtk, to transform the itkImage to vtkImage
		vtkConnectorType::Pointer vtkConnector = vtkConnectorType::New();
		vtkConnector->GetExporter()->SetInput(filter->GetOutput());
		vtkConnector->GetImporter()->Update();

		itkImage = filter->GetOutput();
		// clear previous vtkImage
		vtkImage = NULL;

		// create new vtk image
		vtkImage = vtkSmartPointer <vtkImageData>::New();
		vtkImage->Initialize();
		vtkImage->DeepCopy(vtkConnector->GetImporter()->GetOutput());
		vtkImage->Update();

		isFliped = false;
		this->displayImage(vtkImage);

		filter = NULL;
		vtkConnector = NULL;
	}
}

void ImageWidget::gradientAnisotropicDiffusionFilter()
{
	// create and show the median filter dialog 	
	GADFilterDialog filterDialog(this);
	if (filterDialog.exec()) {

		// if the image is grayscale
		if (imageType.compare("scalar") == 0) {
			// set up gradient anisotropic diffusion filter
			typedef itk::GradientAnisotropicDiffusionImageFilter< ImageType, FloatImageType > FilterType;
			FilterType::Pointer filter = FilterType::New();
			filter->SetInput(itkImage);

			filter->SetNumberOfIterations(filterDialog.iterationsSpinBox->value());
			filter->SetTimeStep(filterDialog.timeStepSpinBox->value());
			filter->SetConductanceParameter(filterDialog.conductanceSpinBox->value());
			filter->Update();			
			
			// cast the float image to scalar image in order to display
			typedef itk::CastImageFilter< FloatImageType, ImageType > CastFilterType;
			CastFilterType::Pointer castFilter = CastFilterType::New();
			castFilter->SetInput(filter->GetOutput());
			
			itkImage = castFilter->GetOutput();

			// setup and connect itk with vtk, to transform the itkImage to vtkImage
			vtkConnectorType::Pointer vtkConnector = vtkConnectorType::New();
			vtkConnector->GetExporter()->SetInput(castFilter->GetOutput());
			vtkConnector->GetImporter()->Update();

			// clear previous vtkImage
			vtkImage = NULL;

			// create new vtk image
			vtkImage = vtkSmartPointer <vtkImageData>::New();
			vtkImage->Initialize();
			vtkImage->DeepCopy(vtkConnector->GetImporter()->GetOutput());
			vtkImage->Update();

			isFliped = false;
			this->displayImage(vtkImage);

			filter = NULL;
			vtkConnector = NULL;
		} else {
			// if image is RGB
			typedef itk::RGBPixel< float > FloatPixelType;
			typedef itk::Image< FloatPixelType, 2 > FloatRGBImageType;
			typedef itk::VectorGradientAnisotropicDiffusionImageFilter< RGBImageType, FloatRGBImageType > FilterType;


			FilterType::Pointer filter = FilterType::New();
			filter->SetInput(rgbItkImage);

			filter->SetNumberOfIterations(filterDialog.iterationsSpinBox->value());
			filter->SetTimeStep(filterDialog.timeStepSpinBox->value());
			filter->SetConductanceParameter(filterDialog.conductanceSpinBox->value());
			filter->Update();

			typedef itk::CastImageFilter< FloatRGBImageType, RGBImageType > CastFilterType;
			CastFilterType::Pointer castFilter = CastFilterType::New();
			castFilter->SetInput(filter->GetOutput());

			rgbItkImage = castFilter->GetOutput();

			// setup and connect itk with vtk, to transform the itkImage to vtkImage
			RGBVtkConnectorType::Pointer vtkConnector = RGBVtkConnectorType::New();
			vtkConnector->GetExporter()->SetInput(castFilter->GetOutput());
			vtkConnector->GetImporter()->Update();

			// clear previous vtkImage
			vtkImage = NULL;

			// create new vtk image
			vtkImage = vtkSmartPointer <vtkImageData>::New();
			vtkImage->Initialize();
			vtkImage->DeepCopy(vtkConnector->GetImporter()->GetOutput());
			vtkImage->Update();

			isFliped = false;
			this->displayImage(vtkImage);

			filter = NULL;
			vtkConnector = NULL;
		}
	}
}

void ImageWidget::displayImage(vtkImageData *image)
{
	if (!isFliped) {
		// flip image in Y axis				
		vtkSmartPointer<vtkImageFlip> flipYFilter = vtkSmartPointer<vtkImageFlip>::New();
		flipYFilter->SetFilteredAxis(1); // flip Y axis
		flipYFilter->SetInput(image);
		flipYFilter->Update();

		actor->SetInput(flipYFilter->GetOutput());
	} else {
		actor->SetInput(image);
	}

	actor->InterpolateOff();

	renderer->AddActor(actor);
	renderer->ResetCamera();
	//	renderWindow->SetSize(640, 480);

	// window interactor style for display images 
	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
	qvtkWidget->SetRenderWindow(renderWindow);

	// set interactor style to the qvtkWidget Interactor
	qvtkWidget->GetInteractor()->SetInteractorStyle(style);

	this->update();
}

void ImageWidget::setITKImageFromVTK()
{
	itkConnectorType::Pointer itkConnector = itkConnectorType::New();

	if (imageType.compare("rgb") == 0) {
		// Must convert image to grayscale because itkVTKImageToImageFilter only accepts single channel images
		vtkSmartPointer<vtkImageLuminance> luminanceFilter =
			vtkSmartPointer<vtkImageLuminance>::New();
		luminanceFilter->SetInput(vtkImage);
		luminanceFilter->Update();

		//get itkImage from vtkImage;  vtkImageData is unsigned char and single channel            
		itkConnector->SetInput(luminanceFilter->GetOutput());
		luminanceFilter = NULL;
	} else {
		itkConnector->SetInput(vtkImage);
	}

	itkConnector->Update();

	itkImage = ImageType::New();
	itkImage->Graft(itkConnector->GetOutput());

	itkConnector = NULL;
}

void ImageWidget::setImageProperties(std::string fileName, bool vervose)
{
	// Obtain image information
	typedef itk::ImageIOBase::IOComponentType ScalarPixelType;

	itk::ImageIOBase::Pointer imageIO =
		itk::ImageIOFactory::CreateImageIO(fileName.c_str(), itk::ImageIOFactory::ReadMode);

	imageIO->SetFileName(fileName);
	imageIO->ReadImageInformation();

	pixelType = imageIO->GetComponentTypeAsString(imageIO->GetComponentType());
	numDimensions = imageIO->GetNumberOfDimensions();
	imageType = imageIO->GetPixelTypeAsString(imageIO->GetPixelType());

	if (vervose) {
		std::cout << "Pixels type: " << pixelType << std::endl;
		std::cout << "Image type: " << imageType << std::endl;
		std::cout << "Num of Dimensions: " << numDimensions << std::endl;
	}
}
