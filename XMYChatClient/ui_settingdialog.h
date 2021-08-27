/********************************************************************************
** Form generated from reading UI file 'settingdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_settingDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_serverip;
    QLineEdit *lineEdit_ip;
    QLabel *label_colon;
    QSpinBox *spinBox_port;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *settingDialog)
    {
        if (settingDialog->objectName().isEmpty())
            settingDialog->setObjectName(QString::fromUtf8("settingDialog"));
        settingDialog->resize(300, 100);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(settingDialog->sizePolicy().hasHeightForWidth());
        settingDialog->setSizePolicy(sizePolicy);
        settingDialog->setMinimumSize(QSize(300, 100));
        settingDialog->setMaximumSize(QSize(300, 100));
        gridLayout = new QGridLayout(settingDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_serverip = new QLabel(settingDialog);
        label_serverip->setObjectName(QString::fromUtf8("label_serverip"));

        horizontalLayout->addWidget(label_serverip);

        lineEdit_ip = new QLineEdit(settingDialog);
        lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));

        horizontalLayout->addWidget(lineEdit_ip);

        label_colon = new QLabel(settingDialog);
        label_colon->setObjectName(QString::fromUtf8("label_colon"));

        horizontalLayout->addWidget(label_colon);

        spinBox_port = new QSpinBox(settingDialog);
        spinBox_port->setObjectName(QString::fromUtf8("spinBox_port"));
        spinBox_port->setMinimum(1);
        spinBox_port->setMaximum(65535);
        spinBox_port->setValue(42000);

        horizontalLayout->addWidget(spinBox_port);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(settingDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(settingDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, settingDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, settingDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(settingDialog);
    } // setupUi

    void retranslateUi(QDialog *settingDialog)
    {
        settingDialog->setWindowTitle(QCoreApplication::translate("settingDialog", "Server settings", nullptr));
        label_serverip->setText(QCoreApplication::translate("settingDialog", "Server IP", nullptr));
        lineEdit_ip->setText(QCoreApplication::translate("settingDialog", "127.0.0.1", nullptr));
        label_colon->setText(QCoreApplication::translate("settingDialog", ":", nullptr));
    } // retranslateUi

};

namespace Ui {
    class settingDialog: public Ui_settingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
