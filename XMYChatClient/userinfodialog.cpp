#include "userinfodialog.h"
#include "ui_userinfodialog.h"

UserInfoDialog::UserInfoDialog(QWidget *parent, QString username, QString email) :
    QDialog(parent),
    ui(new Ui::UserInfoDialog)
{
    ui->setupUi(this);
    QString filename=XMY_Utilities::get_avatar_filename(".cache\\",email);
    if(!QFile(filename).exists()) filename=".cache\\default.png";
    QPixmap pic(filename);
    pic.scaled(ui->label_avatar->size(), Qt::KeepAspectRatio);
    ui->label_avatar->setScaledContents(true);
    ui->label_avatar->setPixmap(pic);
    ui->lineEdit_email->setText(email);
    ui->lineEdit_username->setText(username);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_email->setEnabled(false);
}

UserInfoDialog::~UserInfoDialog()
{
    delete ui;
}

void UserInfoDialog::on_pushButton_select_avatar_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,"Choose a avatar file",".","Images (*.png)");
    if(path.isEmpty()) return;
    QPixmap avatar(path);
    avatar.scaled(ui->label_avatar->size(), Qt::KeepAspectRatio);
    ui->label_avatar->setScaledContents(true);
    ui->label_avatar->setPixmap(avatar);
    data["avatar"]=XMY_Utilities::get_pic_base64(path);
}


void UserInfoDialog::on_lineEdit_username_textEdited(const QString &username)
{
    data.insert("username",username);
}


void UserInfoDialog::on_lineEdit_email_textEdited(const QString &email)
{
    data.insert("email",email);
}


void UserInfoDialog::on_lineEdit_password_textEdited(const QString &password)
{
    data.insert("password",QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha384).toHex());
}

