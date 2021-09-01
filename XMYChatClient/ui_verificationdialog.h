/********************************************************************************
** Form generated from reading UI file 'verificationdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VERIFICATIONDIALOG_H
#define UI_VERIFICATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VerificationDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *VerificationDialog)
    {
        if (VerificationDialog->objectName().isEmpty())
            VerificationDialog->setObjectName(QString::fromUtf8("VerificationDialog"));
        VerificationDialog->resize(450, 100);
        gridLayout = new QGridLayout(VerificationDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(VerificationDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(VerificationDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(VerificationDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(VerificationDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, VerificationDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, VerificationDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(VerificationDialog);
    } // setupUi

    void retranslateUi(QDialog *VerificationDialog)
    {
        VerificationDialog->setWindowTitle(QCoreApplication::translate("VerificationDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("VerificationDialog", "Input the verification code sent to your email:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VerificationDialog: public Ui_VerificationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERIFICATIONDIALOG_H
