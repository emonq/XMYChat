#include "verificationdialog.h"
#include "ui_verificationdialog.h"

VerificationDialog::VerificationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerificationDialog)
{
    ui->setupUi(this);
}

int VerificationDialog::get_code()
{
    return ui->lineEdit->text().toInt();
}

VerificationDialog::~VerificationDialog()
{
    delete ui;
}
