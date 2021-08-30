#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent, loginsession* s_session) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow),
    session(s_session)
{
    ui->setupUi(this);
    qDebug()<<session;
    connect(session,&loginsession::sig_logout,this,&ChatWindow::slot_logout);
    connect(session,&loginsession::sig_receive_message,this,&ChatWindow::slot_receive_message);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::on_pushButton_clicked()
{
    session->logout();
}

void ChatWindow::slot_logout()
{
    QMessageBox msgbox(QMessageBox::Warning,"Logged out","You have logged out");
    msgbox.exec();
    close();
}

void ChatWindow::slot_receive_message(QString from_username, QString msg)
{
    ui->listWidget_messages->addItem(QString("%1:\n%2").arg(from_username,msg));
}


void ChatWindow::on_pushButton_send_clicked()
{
    session->send_message("768412320f7b0aa5812fce428dc4706b3cae50e02a64caa16a782249bfe8efc4b7ef1ccb126255d196047dfedf17a0a9",ui->plainTextEdit_msgedit->toPlainText());
}

void ChatWindow::on_pushButton_search_clicked()
{
    QJsonObject data;

}

