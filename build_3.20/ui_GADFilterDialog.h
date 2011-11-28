/********************************************************************************
** Form generated from reading UI file 'GADFilterDialog.ui'
**
** Created: Mon Nov 28 12:58:59 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GADFILTERDIALOG_H
#define UI_GADFILTERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GADFilterDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_2;
    QDoubleSpinBox *timeStepSpinBox;
    QLabel *label_3;
    QDoubleSpinBox *conductanceSpinBox;
    QLabel *label;
    QSpinBox *iterationsSpinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *GADFilterDialog)
    {
        if (GADFilterDialog->objectName().isEmpty())
            GADFilterDialog->setObjectName(QString::fromUtf8("GADFilterDialog"));
        GADFilterDialog->resize(270, 180);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GADFilterDialog->sizePolicy().hasHeightForWidth());
        GADFilterDialog->setSizePolicy(sizePolicy);
        widget = new QWidget(GADFilterDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(16, 11, 241, 156));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        timeStepSpinBox = new QDoubleSpinBox(widget);
        timeStepSpinBox->setObjectName(QString::fromUtf8("timeStepSpinBox"));
        timeStepSpinBox->setDecimals(3);
        timeStepSpinBox->setMinimum(0.005);
        timeStepSpinBox->setMaximum(10);
        timeStepSpinBox->setSingleStep(0.005);
        timeStepSpinBox->setValue(0.125);

        formLayout->setWidget(1, QFormLayout::FieldRole, timeStepSpinBox);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        conductanceSpinBox = new QDoubleSpinBox(widget);
        conductanceSpinBox->setObjectName(QString::fromUtf8("conductanceSpinBox"));
        conductanceSpinBox->setMinimum(0.01);
        conductanceSpinBox->setSingleStep(0.01);
        conductanceSpinBox->setValue(0.5);

        formLayout->setWidget(2, QFormLayout::FieldRole, conductanceSpinBox);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label);

        iterationsSpinBox = new QSpinBox(widget);
        iterationsSpinBox->setObjectName(QString::fromUtf8("iterationsSpinBox"));
        iterationsSpinBox->setMinimum(1);
        iterationsSpinBox->setValue(5);

        formLayout->setWidget(3, QFormLayout::FieldRole, iterationsSpinBox);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(GADFilterDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), GADFilterDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GADFilterDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(GADFilterDialog);
    } // setupUi

    void retranslateUi(QDialog *GADFilterDialog)
    {
        GADFilterDialog->setWindowTitle(QApplication::translate("GADFilterDialog", "GADFilterDialog", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        GADFilterDialog->setToolTip(QApplication::translate("GADFilterDialog", "Gradient Anisotropic Diffusion Filter Options", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("GADFilterDialog", "Time Step:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GADFilterDialog", "Conductance:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GADFilterDialog", "Number of Iterations:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GADFilterDialog: public Ui_GADFilterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GADFILTERDIALOG_H
