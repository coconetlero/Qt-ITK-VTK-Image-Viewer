/********************************************************************************
** Form generated from reading UI file 'MedianFilterDialog.ui'
**
** Created: Mon Nov 28 13:35:33 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDIANFILTERDIALOG_H
#define UI_MEDIANFILTERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MedianFilterDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBox;

    void setupUi(QDialog *MedianFilterDialog)
    {
        if (MedianFilterDialog->objectName().isEmpty())
            MedianFilterDialog->setObjectName(QString::fromUtf8("MedianFilterDialog"));
        MedianFilterDialog->resize(222, 86);
        buttonBox = new QDialogButtonBox(MedianFilterDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 50, 192, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(MedianFilterDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 10, 126, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setTextFormat(Qt::PlainText);

        horizontalLayout->addWidget(label);

        spinBox = new QSpinBox(layoutWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(50);

        horizontalLayout->addWidget(spinBox);

        layoutWidget->raise();
        buttonBox->raise();

        retranslateUi(MedianFilterDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), MedianFilterDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MedianFilterDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(MedianFilterDialog);
    } // setupUi

    void retranslateUi(QDialog *MedianFilterDialog)
    {
        MedianFilterDialog->setWindowTitle(QApplication::translate("MedianFilterDialog", "Filter Intensity", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MedianFilterDialog", "Intensity:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MedianFilterDialog: public Ui_MedianFilterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIANFILTERDIALOG_H
