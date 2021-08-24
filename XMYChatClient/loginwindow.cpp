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
            ui->label_warnMessage->setText("用户名不能为空！");
            return;
        }
        if(ui->lineEdit_password->text().isEmpty()) {
            ui->label_warnMessage->setText("密码不能为空！");
            return;
        }
    }
    else {
        ui->label_warnMessage->setStyleSheet("color:black;");
        ui->label_warnMessage->setText("登录中……");
    }

}

