/********************************************************************************
** Form generated from reading UI file 'usermainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMAINWINDOW_H
#define UI_USERMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserMainWindow
{
public:
    QWidget *centralwidget;
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_avatar;
    QVBoxLayout *verticalLayout;
    QLabel *label_username;
    QLabel *label_email;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_usersearchinput;
    QPushButton *pushButton_search;
    QLabel *label_friends;
    QListWidget *listWidget_friends;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_editinfo;
    QPushButton *pushButton_logout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_avatar_friend;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_username_friend;
    QLabel *label_email_friend;
    QSplitter *splitter;
    QListWidget *listWidget_messages;
    QPlainTextEdit *plainTextEdit_msginput;
    QPushButton *pushButton_send;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *UserMainWindow)
    {
        if (UserMainWindow->objectName().isEmpty())
            UserMainWindow->setObjectName(QString::fromUtf8("UserMainWindow"));
        UserMainWindow->resize(800, 600);
        centralwidget = new QWidget(UserMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_avatar = new QLabel(centralwidget);
        label_avatar->setObjectName(QString::fromUtf8("label_avatar"));
        label_avatar->setMinimumSize(QSize(100, 100));
        label_avatar->setMaximumSize(QSize(100, 100));

        horizontalLayout_3->addWidget(label_avatar);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_username = new QLabel(centralwidget);
        label_username->setObjectName(QString::fromUtf8("label_username"));

        verticalLayout->addWidget(label_username);

        label_email = new QLabel(centralwidget);
        label_email->setObjectName(QString::fromUtf8("label_email"));

        verticalLayout->addWidget(label_email);


        horizontalLayout_3->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_usersearchinput = new QLineEdit(centralwidget);
        lineEdit_usersearchinput->setObjectName(QString::fromUtf8("lineEdit_usersearchinput"));

        horizontalLayout->addWidget(lineEdit_usersearchinput);

        pushButton_search = new QPushButton(centralwidget);
        pushButton_search->setObjectName(QString::fromUtf8("pushButton_search"));

        horizontalLayout->addWidget(pushButton_search);


        verticalLayout_2->addLayout(horizontalLayout);

        label_friends = new QLabel(centralwidget);
        label_friends->setObjectName(QString::fromUtf8("label_friends"));

        verticalLayout_2->addWidget(label_friends);

        listWidget_friends = new QListWidget(centralwidget);
        listWidget_friends->setObjectName(QString::fromUtf8("listWidget_friends"));
        listWidget_friends->setContextMenuPolicy(Qt::CustomContextMenu);
        listWidget_friends->setIconSize(QSize(70, 70));

        verticalLayout_2->addWidget(listWidget_friends);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_editinfo = new QPushButton(centralwidget);
        pushButton_editinfo->setObjectName(QString::fromUtf8("pushButton_editinfo"));

        horizontalLayout_2->addWidget(pushButton_editinfo);

        pushButton_logout = new QPushButton(centralwidget);
        pushButton_logout->setObjectName(QString::fromUtf8("pushButton_logout"));

        horizontalLayout_2->addWidget(pushButton_logout);


        verticalLayout_2->addLayout(horizontalLayout_2);


        formLayout->setLayout(0, QFormLayout::LabelRole, verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_avatar_friend = new QLabel(centralwidget);
        label_avatar_friend->setObjectName(QString::fromUtf8("label_avatar_friend"));
        label_avatar_friend->setMinimumSize(QSize(100, 100));
        label_avatar_friend->setMaximumSize(QSize(100, 100));

        horizontalLayout_4->addWidget(label_avatar_friend);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_username_friend = new QLabel(centralwidget);
        label_username_friend->setObjectName(QString::fromUtf8("label_username_friend"));

        verticalLayout_3->addWidget(label_username_friend);

        label_email_friend = new QLabel(centralwidget);
        label_email_friend->setObjectName(QString::fromUtf8("label_email_friend"));

        verticalLayout_3->addWidget(label_email_friend);


        horizontalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_4);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        listWidget_messages = new QListWidget(splitter);
        listWidget_messages->setObjectName(QString::fromUtf8("listWidget_messages"));
        splitter->addWidget(listWidget_messages);
        plainTextEdit_msginput = new QPlainTextEdit(splitter);
        plainTextEdit_msginput->setObjectName(QString::fromUtf8("plainTextEdit_msginput"));
        splitter->addWidget(plainTextEdit_msginput);

        verticalLayout_4->addWidget(splitter);

        pushButton_send = new QPushButton(centralwidget);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));

        verticalLayout_4->addWidget(pushButton_send);


        formLayout->setLayout(0, QFormLayout::FieldRole, verticalLayout_4);

        UserMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UserMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        UserMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(UserMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        UserMainWindow->setStatusBar(statusbar);

        retranslateUi(UserMainWindow);

        QMetaObject::connectSlotsByName(UserMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UserMainWindow)
    {
        UserMainWindow->setWindowTitle(QCoreApplication::translate("UserMainWindow", "MainWindow", nullptr));
        label_avatar->setText(QString());
        label_username->setText(QString());
        label_email->setText(QString());
        lineEdit_usersearchinput->setPlaceholderText(QCoreApplication::translate("UserMainWindow", "Search new friend by email", nullptr));
        pushButton_search->setText(QCoreApplication::translate("UserMainWindow", "Search", nullptr));
        label_friends->setText(QCoreApplication::translate("UserMainWindow", "Loading friends:", nullptr));
        pushButton_editinfo->setText(QCoreApplication::translate("UserMainWindow", "Edit info", nullptr));
        pushButton_logout->setText(QCoreApplication::translate("UserMainWindow", "Log out", nullptr));
        label_avatar_friend->setText(QString());
        label_username_friend->setText(QString());
        label_email_friend->setText(QString());
        pushButton_send->setText(QCoreApplication::translate("UserMainWindow", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserMainWindow: public Ui_UserMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMAINWINDOW_H
