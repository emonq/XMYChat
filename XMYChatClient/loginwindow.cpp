#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->pushButton_login->setShortcut(Qt::Key_Enter);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::on_checkBox_stateChanged(int arg1)
{
    switch (arg1) {
    case (Qt::CheckState::Checked): ui->lineEdit_password->setEchoMode(QLineEdit::EchoMode::Normal); break;
    default: ui->lineEdit_password->setEchoMode(QLineEdit::EchoMode::Password);
    }
}


void LoginWindow::on_pushButton_login_clicked()
{
    if(ui->lineEdit_username->text().isEmpty() || ui->lineEdit_password->text().isEmpty()) {
        ui->label_warnMessage->setEnabled(true);
        ui->label_warnMessage->setStyleSheet("color:red;");
        if(ui->lineEdit_username->text().isEmpty()) {
            ui->label_warnMessage->setText("Username cannot be empty!");
            return;
        }
        if(ui->lineEdit_password->text().isEmpty()) {
            ui->label_warnMessage->setText("Password cannot be empty!");
            return;
        }
    }
    else {
        ui->label_warnMessage->setStyleSheet("color:black;");
        ui->label_warnMessage->setText("Logging in...");
        int status;
        if((status=session.login(ui->lineEdit_username->text(), ui->lineEdit_password->text()))==LOGIN_SUCCESS) {
            ui->label_warnMessage->setText("Login successful");
            ui->label_warnMessage->setStyleSheet("color:green;");
        }
        else {
            switch (status) {
                case LOGIN_CONNECTION_ERROR: ui->label_warnMessage->setText("Connection error!");break;
                case LOGIN_INFO_ERROR: ui->label_warnMessage->setText("Username or password error!");break;
                case LOGIN_USER_NOT_FOUND: ui->label_warnMessage->setText("User not found!");break;
                case LOGIN_USER_BANNED: ui->label_warnMessage->setText("You are banned!");break;
                default: ui->label_warnMessage->setText(QString("Unknown error %1").arg(status));
            }
            ui->label_warnMessage->setText("Login failed");
            ui->label_warnMessage->setStyleSheet("color:red;");
        }
    }

}

