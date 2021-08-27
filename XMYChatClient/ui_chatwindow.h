/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatWindow
{
public:
    QWidget *centralwidget;
    QListWidget *listWidget_friends;
    QPlainTextEdit *plainTextEdit_input_message;
    QPushButton *pushButton_send;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *chatWindow)
    {
        if (chatWindow->objectName().isEmpty())
            chatWindow->setObjectName(QString::fromUtf8("chatWindow"));
        chatWindow->resize(800, 600);
        centralwidget = new QWidget(chatWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        listWidget_friends = new QListWidget(centralwidget);
        listWidget_friends->setObjectName(QString::fromUtf8("listWidget_friends"));
        listWidget_friends->setGeometry(QRect(40, 110, 256, 192));
        plainTextEdit_input_message = new QPlainTextEdit(centralwidget);
        plainTextEdit_input_message->setObjectName(QString::fromUtf8("plainTextEdit_input_message"));
        plainTextEdit_input_message->setGeometry(QRect(330, 410, 104, 70));
        pushButton_send = new QPushButton(centralwidget);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));
        pushButton_send->setGeometry(QRect(490, 460, 80, 20));
        chatWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(chatWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        chatWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(chatWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        chatWindow->setStatusBar(statusbar);

        retranslateUi(chatWindow);

        QMetaObject::connectSlotsByName(chatWindow);
    } // setupUi

    void retranslateUi(QMainWindow *chatWindow)
    {
        chatWindow->setWindowTitle(QCoreApplication::translate("chatWindow", "MainWindow", nullptr));
        pushButton_send->setText(QCoreApplication::translate("chatWindow", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatWindow: public Ui_chatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
