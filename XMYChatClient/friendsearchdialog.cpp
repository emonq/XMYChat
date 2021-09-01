#include "friendsearchdialog.h"
#include "ui_friendsearchdialog.h"

FriendSearchDialog::FriendSearchDialog(QWidget *parent, QString username, QString email) :
    QDialog(parent),
    ui(new Ui::FriendSearchDialog)
{
    ui->setupUi(this);
    ui->label_email->setText(email);
    ui->label_username->setText(username);
    ui->label_avatar->setScaledContents(true);
    QPixmap pic(XMY_Utilities::get_avatar_filename(".cache\\", email));
    pic.scaled(ui->label_avatar->size(), Qt::KeepAspectRatio);
    ui->label_avatar->setPixmap(pic);
}

FriendSearchDialog::~FriendSearchDialog()
{
    delete ui;
}
