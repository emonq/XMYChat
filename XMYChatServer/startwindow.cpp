#include "startwindow.h"
#include "ui_startwindow.h"


StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    tcpserver=new XMY_tcpserver;
    connect(tcpserver,&XMY_tcpserver::receive_message,this,&StartWindow::slot_receive_message);
    connect(tcpserver,&XMY_tcpserver::new_log,this,&StartWindow::slot_show_log);
    fill_ip_addr();
    ui->listWidget_logShow->setWordWrap(true);
    ui->listWidget_logShow->setTextElideMode(Qt::ElideNone);
}

StartWindow::~StartWindow()
{
    delete ui;
    delete tcpserver;
}

void StartWindow::show_log(QVariant msg)
{
    QString output=QDateTime::currentDateTime().toString("[yyyy.MM.dd hh:mm:ss] ");
    if(DEBUG_MODE) qDebug()<<output<<msg;
    output+=msg.toString();
    if(output.size()<1000) ui->listWidget_logShow->addItem(output);
    else ui->listWidget_logShow->addItem("Message too large");
    ui->listWidget_logShow->scrollToBottom();
}

void StartWindow::on_pushButton_start_clicked()
{
    if(ui->comboBox_ip->isEnabled()==true){
        QHostAddress ip;
        if(ui->comboBox_ip->currentText().trimmed()=="Any") ip=QHostAddress::Any;
        else ip=QHostAddress(ui->comboBox_ip->currentText().trimmed());
        int port=ui->spinBox_port->value();
        show_log(QString("Starting server on %1, port %2...").arg(ui->comboBox_ip->currentText().trimmed()).arg(port));
        if(tcpserver->start_server(ip,port)){
            ui->comboBox_ip->setEnabled(false);
            ui->spinBox_port->setEnabled(false);
            ui->label_status->setStyleSheet("color: green;");
            ui->label_status->setText("Running");
            ui->pushButton_start->setText("Stop Server");
            show_log("Started.");
        }
        else {
            show_log("Start server failed!");
        }
    }
    else {
        show_log("Stopping...");
        ui->comboBox_ip->setEnabled(true);
        ui->spinBox_port->setEnabled(true);
        tcpserver->stop_server();
        ui->label_status->setStyleSheet("color: red;");
        ui->label_status->setText("Stopped");
        ui->pushButton_start->setText("Start Server");
    }
}


void StartWindow::on_pushButton_clicked()
{
    ui->listWidget_logShow->clear();
}

void StartWindow::on_actionRefresh_IP_triggered()
{
    fill_ip_addr();
    show_log("ip refreshed.");
}

void StartWindow::slot_receive_message(QString msg_from, QString msg)
{
    show_log(QString("Message from %1: %2").arg(msg_from,msg));
}

void StartWindow::slot_show_log(QString msg)
{
    show_log(msg);
}

void StartWindow::fill_ip_addr()
{
    ui->comboBox_ip->clear();
    auto ip=tcpserver->get_addr();
    if(ip.count()>0) {
        ui->pushButton_start->setEnabled(true);
        ui->comboBox_ip->setEnabled(true);
        ui->comboBox_ip->addItem("Any");
        for(auto& i:ip) {
            ui->comboBox_ip->addItem(i.toString());
        }
    }
    else {
        ui->comboBox_ip->setPlaceholderText("No available ip address");
        ui->comboBox_ip->setEnabled(false);
        ui->pushButton_start->setEnabled(false);
    }
}

