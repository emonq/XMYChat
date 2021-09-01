#include "friendsearchdialog.h"
#include "ui_friendsearchdialog.h"

FriendSearchDialog::FriendSearchDialog(loginsession *session, QWidget *parent, QString username, QString email) :
    QDialog(parent),
    ui(new Ui::FriendSearchDialog)
{
    connect(session,&loginsession::avatar_got,this,&FriendSearchDialog::refresh_avatar);
    this->email=email;
    ui->setupUi(this);
    ui->label_email->setText(email);
    ui->label_username->setText(username);
    ui->label_avatar->setScaledContents(true);
    QString filename=XMY_Utilities::get_avatar_filename(".cache\\",email);
    if(!QFile(filename).exists()) filename=".cache\\default.png";
    QPixmap pic(filename);
    pic.scaled(ui->label_avatar->size(), Qt::KeepAspectRatio);
    ui->label_avatar->setPixmap(pic);
}

FriendSearchDialog::~FriendSearchDialog()
{
    delete ui;
}

void FriendSearchDialog::refresh_avatar(QString email)
{
    if(email==this->email) {
        QString filename=XMY_Utilities::get_avatar_filename(".cache\\",email);
        if(!QFile(filename).exists()) filename=".cache\\default.png";
        QPixmap pic(filename);
        pic.scaled(ui->label_avatar->size(), Qt::KeepAspectRatio);
        ui->label_avatar->setPixmap(pic);

    }
}
