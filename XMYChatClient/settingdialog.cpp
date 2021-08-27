#include "settingdialog.h"
#include "ui_settingdialog.h"

settingDialog::settingDialog(QWidget *parent, QString ip, int port) :
    QDialog(parent),
    ui(new Ui::settingDialog)
{
    ui->setupUi(this);
    ui->lineEdit_ip->setText(ip);
    ui->spinBox_port->setValue(port);
}

settingDialog::~settingDialog()
{
    delete ui;
}

QString settingDialog::get_ip()
{
    return ui->lineEdit_ip->text();
}

int settingDialog::get_port()
{
    return ui->spinBox_port->value();
}

