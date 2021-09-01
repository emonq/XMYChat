#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(loginsession* session, QWidget *parent, QString email, QString password) :
    QDialog(parent),
    ui(new Ui::RegisterDialog),
    session(session)
{
    ui->setupUi(this);
    ui->lineEdit_email->setText(email);
    ui->lineEdit_password->setText(password);
    connect(session,&loginsession::register_return,this,&RegisterDialog::register_callback);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

bool RegisterDialog::check_form()
{
    if(ui->lineEdit_email->text().isEmpty() || !XMY_Utilities::check_valid_email(ui->lineEdit_email->text())) {
        ui->label_warn->setText("Please input a valid email.");
        return false;
    }
    if(ui->lineEdit_password->text().isEmpty() || ui->lineEdit_confirm->text()!=ui->lineEdit_password->text()) {
        ui->label_warn->setText("Please check your password.");
        return false;
    }
    return true;
}

void RegisterDialog::set_status(bool status)
{
    ui->lineEdit_email->setEnabled(status);
    ui->lineEdit_password->setEnabled(status);
    ui->lineEdit_confirm->setEnabled(status);
    ui->lineEdit_username->setEnabled(status);
    ui->pushButton_send_code->setEnabled(status);
    ui->pushButton_register->setEnabled(!status);
}

void RegisterDialog::register_callback(int result)
{
    ui->label_warn->setStyleSheet("color:red;");
    switch (result) {
    case REGISTER_SUCCESS: {
        accept();
        break;
    }
    case REGISTER_WAITING_VERIFICATION: {
        ui->label_warn->setText("Code sent. Please input the code sent to your email");
        ui->label_warn->setStyleSheet("color:green;");
        break;
    }
    case REGISTER_VERIFY_ERROR: {
        ui->label_warn->setText("Your code is wrong, please check again!");
        break;
    }
    case REGISTER_USER_EXISTED: {
        ui->label_warn->setText("The user with the same email exists.");
        set_status(true);
        break;
    }
    case REGISTER_INFO_ERROR: {
        ui->label_warn->setText("Please check your info");
        set_status(true);
        break;
    }
    default: {
        ui->label_warn->setText(QString("Unknown error %1").arg(result)) ;
    }
    }
}

void RegisterDialog::on_pushButton_send_code_clicked()
{
    if(!check_form()) return;
    if(session->user_register(ui->lineEdit_email->text(),ui->lineEdit_password->text(),ui->lineEdit_username->text())) set_status(false);
    else {
        ui->label_warn->setText("Connection error");
        ui->label_warn->setStyleSheet("color:red;");
    }
}


void RegisterDialog::on_pushButton_register_clicked()
{
    if(ui->lineEdit_verification_code->text().isEmpty()) {
        ui->label_warn->setText("Please input the verification code!");
        ui->label_warn->setStyleSheet("color:red;");
        return;
    }
    session->email_verify(ui->lineEdit_verification_code->text().toInt());
    ui->label_warn->setText("Verifing your email...");
    ui->label_warn->setStyleSheet("color:black;");
}

