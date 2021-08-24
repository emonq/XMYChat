#include "loginwindow.h"
#include "ui_startwindow.h"

bool isRunning=false;

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
}

StartWindow::~StartWindow()
{
    delete ui;
}


void StartWindow::on_pushButton_start_clicked()
{
    if(isRunning==false){
        ui->listWidget_logShow->addItem("Starting...");
        ui->label_status->setText("Running");
        ui->label_status->setStyleSheet("color: green;");
        ui->pushButton_start->setText("Stop Server");
        isRunning=true;
    }
    else {
        ui->listWidget_logShow->addItem("Stopping...");
        ui->label_status->setText("Stopped");
        ui->label_status->setStyleSheet("color: red;");
        ui->pushButton_start->setText("Start Server");
        isRunning=false;
    }
}


void StartWindow::on_pushButton_clicked()
{
    ui->listWidget_logShow->clear();
}

