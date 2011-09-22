/* 
 * File:   GADFilterDialog.h
 * Author: zian
 *
 * Created on 22 de septiembre de 2011, 14:07
 */

#ifndef _GADFILTERDIALOG_H
#define	_GADFILTERDIALOG_H

#include <QDialog>

#include "ui_GADFilterDialog.h"

class GADFilterDialog : public QDialog, public Ui::GADFilterDialog {
    Q_OBJECT

public:
    
    GADFilterDialog(QWidget *parent = 0);
    
    virtual ~GADFilterDialog();

private:

};

#endif	/* _GADFILTERDIALOG_H */


