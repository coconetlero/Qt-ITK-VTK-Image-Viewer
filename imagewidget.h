/* 
 * File:   imagewidget.h
 * Author: zian
 *
 * Created on 19 de septiembre de 2011, 19:34
 */

#ifndef IMAGEWIDGET_H
#define	IMAGEWIDGET_H

#include <QtGui>
#include <QWidget>
#include <QVTKWidget.h>

#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

#include <itkImage.h>


typedef itk::Image< unsigned char, 2 > ImageType;

class ImageWidget : public QWidget {
    
    Q_OBJECT
    
public:
     /** 
      * Constructor for this ImageWidget 
      */
    ImageWidget(QWidget *parent = 0);

    /** 
     * Destructor for this ImageWidget 
     */
    virtual ~ImageWidget();

    /**
     * load an display an image from file
     */
    void open();
    
    /**
     * Apply a median fiter to the itkImage
     */
    void medianFilter();
    
private:
    
    QVTKWidget *qvtkWidget;
    
    /** The image displayed for this window */
    ImageType::Pointer itkImage;

    /** The VTK image to display in this window */
    vtkSmartPointer <vtkImageData> vtkImage;
        
    vtkSmartPointer<vtkImageActor> actor;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    
    
    /**
     * to display the loaded image in the QVTKwidget
     * @param image vtkImageData
     */
    void displayImage(vtkImageData *image);

};

#endif	/* IMAGEWIDGET_H */

