#include <QtGui>

#include "imageviewer.h"

ImageViewer::ImageViewer(QWidget *parent) : QMainWindow(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	createActions();
	createMenus();
	createStatusBar();    
}

ImageViewer::~ImageViewer()
{
	this->imageWidget = NULL;

}

void ImageViewer::open()
{
    
	if (!imageWidget) {
		this->imageWidget = new ImageWidget();
//        this->imageWidget->openWithITK();
		this->imageWidget->open();
		
        this->setCentralWidget(imageWidget);
		this->setWindowTitle(tr("Image Viewer"));
		this->resize(640, 480);
	} else {
		ImageViewer *viewer = new ImageViewer();
		viewer->imageWidget = new ImageWidget();
//        viewer->imageWidget->openWithITK();        
		viewer->imageWidget->open();
        
		viewer->setCentralWidget(viewer->imageWidget);
		viewer->setWindowTitle(tr("Image Viewer"));
		viewer->resize(640, 480);
		viewer->show();
	}
}

void ImageViewer::saveAs()
{

}

void ImageViewer::medianFilter()
{
	this->imageWidget->medianFilter();
}

void ImageViewer::gradientAnisotropicDiffusionFilter()
{
	this->imageWidget->gradientAnisotropicDiffusionFilter();
}

void ImageViewer::about()
{
	QMessageBox::about(this, tr("About Image Viewer"),
		tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
		"and QScrollArea to display an image. QLabel is typically used "
		"for displaying a text, but it can also display an image. "
		"QScrollArea provides a scrolling view around another widget. "
		"If the child widget exceeds the size of the frame, QScrollArea "
		"automatically provides scroll bars. </p><p>The example "
		"demonstrates how QLabel's ability to scale its contents "
		"(QLabel::scaledContents), and QScrollArea's ability to "
		"automatically resize its contents "
		"(QScrollArea::widgetResizable), can be used to implement "
		"zooming and scaling features. </p><p>In addition the example "
		"shows how to use QPainter to print an image.</p>"));
}

void ImageViewer::createActions()
{
	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcut(tr("Ctrl+O"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	saveAsAct = new QAction(tr("Save As..."), this);
	saveAsAct->setShortcut(tr("Ctrl+Shift+S"));
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

	medianFilterAct = new QAction(tr("Median Filter"), this);
	medianFilterAct->setStatusTip(tr("Apply a median filter to image"));
	connect(medianFilterAct, SIGNAL(triggered()), this, SLOT(medianFilter()));

	GADFilterAct = new QAction(tr("Gradient Anisotropic Filter"), this);
	connect(GADFilterAct, SIGNAL(triggered()), this, SLOT(gradientAnisotropicDiffusionFilter()));

	aboutAct = new QAction(tr("&About"), this);
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAct = new QAction(tr("About &Qt"), this);
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void ImageViewer::createMenus()
{
	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAsAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	filterMenu = new QMenu(tr("&Filter"), this);
	filterMenu->addAction(medianFilterAct);
	filterMenu->addAction(GADFilterAct);

	helpMenu = new QMenu(tr("&Help"), this);
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(filterMenu);
	menuBar()->addMenu(helpMenu);
}

void ImageViewer::createStatusBar()
{
	statusLabel = new QLabel("Basic Image Viewer");
	statusLabel->setAlignment(Qt::AlignHCenter);
    statusLabel->setMaximumSize(statusLabel->sizeHint());

	statusBar()->addWidget(statusLabel);
}