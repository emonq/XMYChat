#include "startwindow.h"
#include "ui_startwindow.h"


StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
    , tcpserver(new Q_tcpserver)
{
    ui->setupUi(this);
    fill_ip_addr();
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::show_log(QString msg)
{
    if(DEBUG_MODE) qDebug()<<msg;
    ui->listWidget_logShow->addItem(msg);

}


void StartWindow::on_pushButton_start_clicked()
{
    if(ui->comboBox_ip->isEnabled()==true){
        QHostAddress ip;
        if(ui->comboBox_ip->currentText()=="Any") ip=QHostAddress::Any;
        else ip=QHostAddress(ui->comboBox_ip->currentText());
        int port=ui->spinBox_port->value();
        show_log(QString("Starting server on %1, port %2...").arg(ui->comboBox_ip->currentText().trimmed()).arg(port));
        ui->comboBox_ip->setEnabled(false);
        ui->spinBox_port->setEnabled(false);

        tcpserver->start_server(ip,port);
        ui->label_status->setStyleSheet("color: green;");
        ui->label_status->setText("Running");
        ui->pushButton_start->setText("Stop Server");
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

void StartWindow::fill_ip_addr()
{
    ui->comboBox_ip->clear();
    auto ip=tcpserver->get_addr();
    if(ip.count()>0) {
        ui->comboBox_ip->setEnabled(true);
        ui->comboBox_ip->addItem("Any");
        for(auto& i:ip) {
            ui->comboBox_ip->addItem(i.toString());
        }
    }
    else {
        ui->comboBox_ip->setPlaceholderText("No available ip address");
        ui->comboBox_ip->setEnabled(false);
    }
}

