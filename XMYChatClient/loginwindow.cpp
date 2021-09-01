#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
    , session(new loginsession)
{
    ui->setupUi(this);
    ui->pushButton_login->setShortcut(Qt::Key_Enter);
    connect(session,&loginsession::login_return,this,&LoginWindow::slot_login_callback);
    connect(session,&loginsession::general_return,this,&LoginWindow::slot_general_callback);
    settings=new xmyUserSettings;
    ui->pushButton_login->setDefault(true);
    connect(ui->lineEdit_password,&QLineEdit::returnPressed,ui->pushButton_login,&QPushButton::click);
    connect(ui->lineEdit_email,&QLineEdit::returnPressed,this,[=](){
        ui->lineEdit_password->setFocus();
    });
    QVariant ip, port;
    if(!settings->get_value("Server ip", ip)) settings->set_value("Server ip","127.0.0.1");
    if(!settings->get_value("Server port", port)) settings->set_value("Server port",42000);
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete settings;
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
    if(check_form()) {
        ui->label_warnMessage->setStyleSheet("color:black;");
        ui->label_warnMessage->setText("Logging in...");
        set_widgets(false);
        session->user_login(ui->lineEdit_email->text().trimmed().toLower(), ui->lineEdit_password->text());
    }
}


void LoginWindow::on_actionServer_Settings_triggered()
{
    QVariant ip, port;
    if(!settings->get_value("Server ip", ip)) ip="127.0.0.1";
    if(!settings->get_value("Server port", port)) port=42000;
    settingDialog *settingwindow=new settingDialog(this, ip.toString(), port.toInt());
    int res=settingwindow->exec();
    if(res==1) {
        settings->set_value("Server ip", settingwindow->get_ip());
        settings->set_value("Server port", settingwindow->get_port());
        session->establish_connect();
    }
    settingwindow->deleteLater();
}

void LoginWindow::slot_login_callback(int result)
{
    if(result==LOGIN_SUCCESS) {
        ui->label_warnMessage->setText("Login successful");
        ui->label_warnMessage->setStyleSheet("color:green;");
        UserMainWindow* mainwindow=new UserMainWindow(nullptr,session);
        mainwindow->show();
        close();
    }
    else {
        switch (result) {
        case LOGIN_INFO_ERROR: ui->label_warnMessage->setText("Username or password error!");break;
        case LOGIN_USER_NOT_FOUND: ui->label_warnMessage->setText("User not found!");break;
        case LOGIN_USER_BANNED: ui->label_warnMessage->setText("You are banned!");break;
        case LOGIN_USER_WAITING_VERIFICATION: verify(); break;
        default: ui->label_warnMessage->setText(QString("Unknown error %1").arg(result));
        }
        ui->label_warnMessage->setStyleSheet("color:red;");
    }
    set_widgets(true);
}


void LoginWindow::slot_general_callback(int result)
{
    ui->label_warnMessage->setStyleSheet("color:red;");
    switch (result) {
    case CONNECTION_CONNECTED: {
        ui->label_warnMessage->setStyleSheet("color:green");
        ui->label_warnMessage->setText("Connected to server");
        break;
    }
    case CONNECTION_ERROR: ui->label_warnMessage->setText("Connection error!");break;
    case CONNECTION_TIMEOUT: ui->label_warnMessage->setText("Connection timeout!"); break;
    default: ui->label_warnMessage->setText(QString("Unknown error %1").arg(result));
    }
    set_widgets(true);
}


void LoginWindow::on_pushButton_register_clicked()
{
    RegisterDialog* regdlg=new RegisterDialog(session,this,ui->lineEdit_email->text(),ui->lineEdit_password->text());
    if(regdlg->exec()==1) {
        ui->lineEdit_email->setText(session->info.value("email"));
        ui->label_warnMessage->setText("Register success!");
        ui->label_warnMessage->setStyleSheet("color:green;");
        ui->lineEdit_password->setFocus();
    }
}

bool LoginWindow::check_form()
{
    if(ui->lineEdit_email->text().isEmpty() || ui->lineEdit_password->text().isEmpty()) {
        ui->label_warnMessage->setStyleSheet("color:red;");
        if(ui->lineEdit_email->text().isEmpty()) {
            ui->label_warnMessage->setText("Username cannot be empty!");
            return false;
        }
        if(ui->lineEdit_password->text().isEmpty()) {
            ui->label_warnMessage->setText("Password cannot be empty!");
            return false;
        }
    }
    return true;
}

void LoginWindow::verify()
{
    VerificationDialog* vdialog=new VerificationDialog(this);
    if(vdialog->exec()==1) {
        session->email_verify(vdialog->get_code());
    }
    vdialog->deleteLater();
}

void LoginWindow::set_widgets(bool status)
{
    ui->lineEdit_password->setEnabled(status);
    ui->lineEdit_email->setEnabled(status);
    ui->pushButton_login->setEnabled(status);
    ui->pushButton_register->setEnabled(status);
}

