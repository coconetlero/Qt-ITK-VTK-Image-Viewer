/* 
 * File:   medianFilterDialog.h
 * Author: zian
 *
 * Created on 14 de septiembre de 2011, 16:52
 */

#ifndef MEDIANFILTERDIALOG_H
#define	MEDIANFILTERDIALOG_H

#include <QDialog>

#include "ui_MedianFilterDialog.h"

class MedianFilterDialog : public QDialog, public Ui::MedianFilterDialog {
    Q_OBJECT
    
public:
    
    MedianFilterDialog(QWidget *parent = 0);
    virtual ~MedianFilterDialog();

private:

};

#endif	/* MEDIANFILTERDIALOG_H */

