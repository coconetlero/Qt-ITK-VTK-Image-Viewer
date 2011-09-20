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

    void open();

    void medianFilter();

    void about();

private:

    void createActions();
    void createMenus();
    
    ImageWidget *imageWidget;

    QAction *openAct;
    QAction *exitAct;    
    QAction *aboutAct;
    QAction *aboutQtAct;

    QAction *medianFilterAct;
    
    QMenu *fileMenu;
    QMenu *filterMenu;
    QMenu *helpMenu;
};

#endif
