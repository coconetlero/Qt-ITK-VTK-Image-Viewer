#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>

#include "imagewidget.h"

class QAction;
class QMenu;
class QMenuBar;
class QScrollArea;
class QScrollBar;
class QVBoxLayout;

class ImageViewer : public QMainWindow {
    Q_OBJECT

public:

    ImageViewer(QWidget* parent = 0);
    ~ImageViewer();

protected:
    //    void closeEvent(QCloseEvent *event);


private slots:

    /**
     * Load and display an image from file
     */
    void open();

    /**
     * Save as, to the disk, displayed image 
     */
    void saveAs();

    /**
     * Apply median filter to image
     */
    void medianFilter();

    /**
     * apply an Anisotropic diffusion filter to image
     */
    void gradientAnisotropicDiffusionFilter();

    /**
     * 
     */
    void about();

private:
    
    void createActions();
    void createMenus();
    void createStatusBar();

    ImageWidget *imageWidget;

    QAction *openAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QAction *medianFilterAct;
    QAction *GADFilterAct;

    QMenu *fileMenu;
    QMenu *filterMenu;
    QMenu *helpMenu;
    
    QLabel *statusLabel;
};

#endif
