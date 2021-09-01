/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QAction *actionServer_Settings;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_title;
    QGridLayout *gridLayout_input;
    QHBoxLayout *horizontalLayout_password;
    QLabel *label_password;
    QLineEdit *lineEdit_password;
    QHBoxLayout *horizontalLayout_username;
    QLabel *label_email;
    QLineEdit *lineEdit_email;
    QCheckBox *checkBox;
    QLabel *label_warnMessage;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_register;
    QPushButton *pushButton_login;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QString::fromUtf8("LoginWindow"));
        LoginWindow->resize(500, 300);
        LoginWindow->setMinimumSize(QSize(500, 300));
        LoginWindow->setMaximumSize(QSize(500, 300));
        actionServer_Settings = new QAction(LoginWindow);
        actionServer_Settings->setObjectName(QString::fromUtf8("actionServer_Settings"));
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_title = new QLabel(centralwidget);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setMinimumSize(QSize(0, 50));
        label_title->setMaximumSize(QSize(16777215, 50));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(26);
        font.setBold(true);
        label_title->setFont(font);
        label_title->setLayoutDirection(Qt::LeftToRight);
        label_title->setInputMethodHints(Qt::ImhNone);
        label_title->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_title);

        gridLayout_input = new QGridLayout();
        gridLayout_input->setObjectName(QString::fromUtf8("gridLayout_input"));
        gridLayout_input->setContentsMargins(-1, 40, -1, 20);
        horizontalLayout_password = new QHBoxLayout();
        horizontalLayout_password->setObjectName(QString::fromUtf8("horizontalLayout_password"));
        label_password = new QLabel(centralwidget);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        label_password->setMinimumSize(QSize(70, 0));

        horizontalLayout_password->addWidget(label_password);

        lineEdit_password = new QLineEdit(centralwidget);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setEchoMode(QLineEdit::Password);

        horizontalLayout_password->addWidget(lineEdit_password);


        gridLayout_input->addLayout(horizontalLayout_password, 1, 0, 1, 1);

        horizontalLayout_username = new QHBoxLayout();
        horizontalLayout_username->setObjectName(QString::fromUtf8("horizontalLayout_username"));
        label_email = new QLabel(centralwidget);
        label_email->setObjectName(QString::fromUtf8("label_email"));
        label_email->setMinimumSize(QSize(70, 0));

        horizontalLayout_username->addWidget(label_email);

        lineEdit_email = new QLineEdit(centralwidget);
        lineEdit_email->setObjectName(QString::fromUtf8("lineEdit_email"));
        lineEdit_email->setClearButtonEnabled(true);

        horizontalLayout_username->addWidget(lineEdit_email);


        gridLayout_input->addLayout(horizontalLayout_username, 0, 0, 1, 1);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setFocusPolicy(Qt::NoFocus);

        gridLayout_input->addWidget(checkBox, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_input);

        label_warnMessage = new QLabel(centralwidget);
        label_warnMessage->setObjectName(QString::fromUtf8("label_warnMessage"));
        label_warnMessage->setEnabled(true);
        label_warnMessage->setMaximumSize(QSize(16777215, 20));
        label_warnMessage->setStyleSheet(QString::fromUtf8("color:red;"));

        verticalLayout->addWidget(label_warnMessage);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_register = new QPushButton(centralwidget);
        pushButton_register->setObjectName(QString::fromUtf8("pushButton_register"));
        pushButton_register->setMaximumSize(QSize(100, 16777215));
        pushButton_register->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pushButton_register);

        pushButton_login = new QPushButton(centralwidget);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_login->sizePolicy().hasHeightForWidth());
        pushButton_login->setSizePolicy(sizePolicy);
        pushButton_login->setMaximumSize(QSize(200, 16777215));
        pushButton_login->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(pushButton_login);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        LoginWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 500, 22));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        LoginWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(LoginWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        LoginWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(lineEdit_email, lineEdit_password);
        QWidget::setTabOrder(lineEdit_password, pushButton_login);
        QWidget::setTabOrder(pushButton_login, pushButton_register);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionServer_Settings);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "XMYChat", nullptr));
        actionServer_Settings->setText(QCoreApplication::translate("LoginWindow", "Server Settings", nullptr));
        label_title->setText(QCoreApplication::translate("LoginWindow", "Welcome to XMYChat", nullptr));
        label_password->setText(QCoreApplication::translate("LoginWindow", "Password", nullptr));
        label_email->setText(QCoreApplication::translate("LoginWindow", "Email", nullptr));
        checkBox->setText(QCoreApplication::translate("LoginWindow", "Show Password", nullptr));
        label_warnMessage->setText(QCoreApplication::translate("LoginWindow", "Connection error!", nullptr));
        pushButton_register->setText(QCoreApplication::translate("LoginWindow", "Register", nullptr));
        pushButton_login->setText(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        menu->setTitle(QCoreApplication::translate("LoginWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
