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

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkMedianImageFilter.h>

#include "imagewidget.h"
#include "medianFilterDialog.h"

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent) {

    this->setAttribute(Qt::WA_DeleteOnClose);

    qvtkWidget = new QVTKWidget(this);
    //    qvtkWidget->resize(640, 480);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(qvtkWidget);
    this->setLayout(layout);


    actor = vtkSmartPointer<vtkImageActor>::New();

    // A renderer and render window
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

}

ImageWidget::~ImageWidget() {
    qvtkWidget = NULL;
    itkImage = NULL;
    vtkImage = NULL;
}

void ImageWidget::open() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {

        // Obtain image information
        this->setImageProperties(fileName.toStdString(), true);

        // reads an vtkImage for display purposes
        vtkSmartPointer <vtkImageReader2Factory> readerFactory =
                vtkSmartPointer <vtkImageReader2Factory>::New();
        vtkSmartPointer <vtkImageReader2> reader =
                readerFactory->CreateImageReader2(fileName.toAscii().data());

        reader->SetFileName(fileName.toAscii().data());
        reader->Update();

        vtkImage = reader->GetOutput();

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

void ImageWidget::medianFilter() {
    // create and show the median filter dialog 
    MedianFilterDialog filterDialog(this);
    if (filterDialog.exec()) {
        // get selected value
        int intensity = filterDialog.spinBox->value();

        // if the itkImage is not loaded, then vtkImage is converted to itkImage 
        if (itkImage.IsNull()) {
            this->setITKImageFromVTK();
        }

        // set up median filter
        typedef itk::MedianImageFilter<ImageType, ImageType > FilterType;

        FilterType::Pointer filter = FilterType::New();
        FilterType::InputSizeType radius;
        radius.Fill(intensity);

        filter->SetRadius(radius);
        filter->SetInput(itkImage);

        // setup and connect itk with vtk, to transform the itkImage to vtkImage
        vtkConnectorType::Pointer vtkConnector = vtkConnectorType::New();
        vtkConnector->GetExporter()->SetInput(filter->GetOutput());
        vtkConnector->GetImporter()->Update();


        // clear previous vtkImage
        vtkImage = NULL;

        // create new vtk image
        vtkImage = vtkSmartPointer <vtkImageData>::New();
        vtkImage->Initialize();
        vtkImage->DeepCopy(vtkConnector->GetImporter()->GetOutput());
        vtkImage->Update();

        this->displayImage(vtkImage);

        filter = NULL;
        vtkConnector = NULL;
    }

}

void ImageWidget::displayImage(vtkImageData *image) {
    actor->SetInput(image);
    actor->InterpolateOff();

    renderer->AddActor(actor);
    renderer->ResetCamera();
    renderWindow->SetSize(640, 480);

    qvtkWidget->SetRenderWindow(renderWindow);

    this->update();
}

void ImageWidget::setITKImageFromVTK() {
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

void ImageWidget::setImageProperties(std::string fileName, bool vervose) {
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
