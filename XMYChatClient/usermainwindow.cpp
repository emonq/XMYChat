#include "usermainwindow.h"
#include "ui_usermainwindow.h"

UserMainWindow::UserMainWindow(QWidget *parent, loginsession* session) :
    QMainWindow(parent),
    ui(new Ui::UserMainWindow),
    session(session)
{
    ui->setupUi(this);
    connect(session,&loginsession::sig_logout,this,&UserMainWindow::slot_logout);
    connect(session,&loginsession::sig_receive_message,this,&UserMainWindow::slot_receive_message);
    ui->label_avatar->setScaledContents(true);
    connect(session,&loginsession::info_refreshed,this,&UserMainWindow::slot_info_refresh);
    connect(session,&loginsession::avatar_got,this,&UserMainWindow::slot_avatar_got);
    connect(session,&loginsession::friend_list_refreshed,this,&UserMainWindow::slot_friend_list_refreshed);
    session->get_user_info();

//    session->fetch_friend_list();
//    session->get_avatar();
}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

void UserMainWindow::slot_logout()
{
    QMessageBox msgbox(QMessageBox::Warning,"Logged out","You have logged out");
    msgbox.exec();
    close();
}

void UserMainWindow::slot_receive_message(QString from_email)
{

}

void UserMainWindow::on_pushButton_send_clicked()
{

}

void UserMainWindow::slot_info_refresh()
{
    fill_user_info();
    session->get_avatar();
}

void UserMainWindow::slot_friend_list_refreshed()
{
    ui->listWidget_friends->clear();
    for(auto &i:session->friends) {
        QListWidgetItem *item=new QListWidgetItem(ui->listWidget_friends);
        item->setIcon(QIcon(XMY_Utilities::get_avatar_filename(".cache\\",i.email)));
        item->setText(i.username+'\n'+i.email);
        qDebug()<<i.username+'\n'+i.email;
        ui->listWidget_friends->addItem(item);
    }
}

void UserMainWindow::slot_avatar_got(QString email)
{
    if(email==session->info.value("email")) {
        fill_user_info();
    }
}


void UserMainWindow::on_pushButton_logout_clicked()
{
    slot_logout();
}


void UserMainWindow::on_pushButton_editinfo_clicked()
{
    qDebug()<<session->info;
    UserInfoDialog* infodialog=new UserInfoDialog(this,session->info["username"],session->info["email"]);
    if(infodialog->exec()==QDialog::Accepted) {
        QJsonObject data;
        data.insert("type",TYPE_INFO_MODIFY);
        data.insert("email",session->info["email"]);
        if(infodialog->data.contains("avatar")) XMY_Utilities::save_pic_from_base64(infodialog->data.value("avatar"),XMY_Utilities::get_avatar_filename(".cache\\",session->info["email"]));
        for(QHash<QString, QString>::iterator i=infodialog->data.begin();i!=infodialog->data.end();i++) {
            data[i.key()]=i.value();
            session->info[i.key()]=i.value();
        }
        session->user_info_modify(data);
        qDebug()<<data;
        fill_user_info();
    }
    infodialog->deleteLater();
}

void UserMainWindow::fill_user_info()
{
    QPixmap avatar(".cache\\"+XMY_Utilities::emailtomd5(session->info["email"])+".png");
    avatar.scaled(ui->label_avatar->size(), Qt::KeepAspectRatio);
    ui->label_avatar->setPixmap(avatar);
    ui->label_email->setText(session->info["email"]);
    ui->label_username->setText(session->info["username"]);
    setWindowTitle(session->info["email"]);
}



void UserMainWindow::on_listWidget_friends_itemClicked(QListWidgetItem *item)
{
    QStringList info=item->text().split('\n');
    ui->label_email_friend->setText(info[1]);
    ui->label_username_friend->setText(info[0]);
}

