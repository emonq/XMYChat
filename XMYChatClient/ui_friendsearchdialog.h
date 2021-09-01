/********************************************************************************
** Form generated from reading UI file 'friendsearchdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDSEARCHDIALOG_H
#define UI_FRIENDSEARCHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FriendSearchDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_avatar;
    QVBoxLayout *verticalLayout;
    QLabel *label_username;
    QLabel *label_email;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FriendSearchDialog)
    {
        if (FriendSearchDialog->objectName().isEmpty())
            FriendSearchDialog->setObjectName(QString::fromUtf8("FriendSearchDialog"));
        FriendSearchDialog->resize(300, 150);
        FriendSearchDialog->setMinimumSize(QSize(300, 150));
        FriendSearchDialog->setMaximumSize(QSize(300, 150));
        verticalLayout_2 = new QVBoxLayout(FriendSearchDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_avatar = new QLabel(FriendSearchDialog);
        label_avatar->setObjectName(QString::fromUtf8("label_avatar"));
        label_avatar->setMinimumSize(QSize(100, 100));
        label_avatar->setMaximumSize(QSize(100, 100));

        horizontalLayout->addWidget(label_avatar);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_username = new QLabel(FriendSearchDialog);
        label_username->setObjectName(QString::fromUtf8("label_username"));

        verticalLayout->addWidget(label_username);

        label_email = new QLabel(FriendSearchDialog);
        label_email->setObjectName(QString::fromUtf8("label_email"));

        verticalLayout->addWidget(label_email);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(FriendSearchDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(FriendSearchDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, FriendSearchDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, FriendSearchDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(FriendSearchDialog);
    } // setupUi

    void retranslateUi(QDialog *FriendSearchDialog)
    {
        FriendSearchDialog->setWindowTitle(QCoreApplication::translate("FriendSearchDialog", "Do you want to add to contact?", nullptr));
        label_avatar->setText(QString());
        label_username->setText(QString());
        label_email->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FriendSearchDialog: public Ui_FriendSearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDSEARCHDIALOG_H
