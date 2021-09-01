/********************************************************************************
** Form generated from reading UI file 'userinfodialog.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINFODIALOG_H
#define UI_USERINFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UserInfoDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_avatar;
    QPushButton *pushButton_select_avatar;
    QFormLayout *formLayout;
    QLineEdit *lineEdit_email;
    QLabel *label_email;
    QLabel *label_password;
    QLineEdit *lineEdit_password;
    QLabel *label_username;
    QLineEdit *lineEdit_username;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *UserInfoDialog)
    {
        if (UserInfoDialog->objectName().isEmpty())
            UserInfoDialog->setObjectName(QString::fromUtf8("UserInfoDialog"));
        UserInfoDialog->resize(400, 200);
        UserInfoDialog->setMinimumSize(QSize(400, 200));
        UserInfoDialog->setMaximumSize(QSize(400, 200));
        gridLayout = new QGridLayout(UserInfoDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_avatar = new QLabel(UserInfoDialog);
        label_avatar->setObjectName(QString::fromUtf8("label_avatar"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_avatar->sizePolicy().hasHeightForWidth());
        label_avatar->setSizePolicy(sizePolicy);
        label_avatar->setMinimumSize(QSize(100, 100));
        label_avatar->setMaximumSize(QSize(100, 100));

        verticalLayout->addWidget(label_avatar);

        pushButton_select_avatar = new QPushButton(UserInfoDialog);
        pushButton_select_avatar->setObjectName(QString::fromUtf8("pushButton_select_avatar"));

        verticalLayout->addWidget(pushButton_select_avatar);


        horizontalLayout->addLayout(verticalLayout);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        lineEdit_email = new QLineEdit(UserInfoDialog);
        lineEdit_email->setObjectName(QString::fromUtf8("lineEdit_email"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_email);

        label_email = new QLabel(UserInfoDialog);
        label_email->setObjectName(QString::fromUtf8("label_email"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_email);

        label_password = new QLabel(UserInfoDialog);
        label_password->setObjectName(QString::fromUtf8("label_password"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_password);

        lineEdit_password = new QLineEdit(UserInfoDialog);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_password);

        label_username = new QLabel(UserInfoDialog);
        label_username->setObjectName(QString::fromUtf8("label_username"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_username);

        lineEdit_username = new QLineEdit(UserInfoDialog);
        lineEdit_username->setObjectName(QString::fromUtf8("lineEdit_username"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_username);


        horizontalLayout->addLayout(formLayout);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(UserInfoDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(UserInfoDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, UserInfoDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, UserInfoDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(UserInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *UserInfoDialog)
    {
        UserInfoDialog->setWindowTitle(QCoreApplication::translate("UserInfoDialog", "User info edit", nullptr));
        label_avatar->setText(QString());
        pushButton_select_avatar->setText(QCoreApplication::translate("UserInfoDialog", "Select", nullptr));
        label_email->setText(QCoreApplication::translate("UserInfoDialog", "email", nullptr));
        label_password->setText(QCoreApplication::translate("UserInfoDialog", "password", nullptr));
        label_username->setText(QCoreApplication::translate("UserInfoDialog", "username", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserInfoDialog: public Ui_UserInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINFODIALOG_H
