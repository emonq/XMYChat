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
    ui->label_avatar_friend->setScaledContents(true);
    connect(session,&loginsession::info_refreshed,this,&UserMainWindow::slot_info_refresh);
    connect(session,&loginsession::avatar_got,this,&UserMainWindow::slot_avatar_got);
    connect(session,&loginsession::friend_list_refreshed,this,&UserMainWindow::slot_friend_list_refreshed);
    connect(session,&loginsession::user_found,this,&UserMainWindow::slot_user_found);
    connect(session,&loginsession::user_not_found,this,[=](){
        QMessageBox warning(QMessageBox::Warning,"Error","User not found",QMessageBox::Ok,this);
        warning.exec();
    });
    connect(session,&loginsession::send_message_failed,this,[=](){
        QMessageBox warning(QMessageBox::Warning,"Message send error","Your message is failed to send. It may because your friend is offline currently.",QMessageBox::Ok,this);
        warning.exec();
    });
    session->get_user_info();
    ui->pushButton_send->setEnabled(false);
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

void UserMainWindow::slot_receive_message(chatMessage msg)
{
    if(msg.sender==ui->label_email_friend->text()){
        show_messages();
    }
    else {
        session->friend_item.value(msg.sender)->setBackground(QColor("pink"));
    }
}

void UserMainWindow::on_pushButton_send_clicked()
{
    QString to_email=ui->label_email_friend->text().trimmed().toLower();
    QString msg=ui->plainTextEdit_msginput->toPlainText();
    session->send_message(to_email,msg);
    ui->plainTextEdit_msginput->clear();
    ui->listWidget_messages->addItem(XMY_Utilities::get_time_string()+" - "+session->info.value("email")+"\n"+msg);
    ui->listWidget_messages->scrollToBottom();
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
        item->setBackground(QColor("white"));
        item->setIcon(QIcon(XMY_Utilities::get_avatar_filename(".cache\\",i.email)));
        item->setText(i.username+'\n'+i.email);
        session->friend_item[i.email]=item;
        ui->listWidget_friends->addItem(item);
    }
    ui->label_friends->setText(QString("%1 friends:").arg(session->friends.count()));
}

void UserMainWindow::slot_avatar_got(QString email)
{
    QString filename=XMY_Utilities::get_avatar_filename(".cache\\",email);
    QPixmap pic(filename);
    if(email==session->info.value("email")) {
        ui->label_avatar->setPixmap(pic);
    }
    else {
        session->friend_item[email]->setIcon(pic);
    }
}

void UserMainWindow::slot_user_found(userStruct user)
{
    FriendSearchDialog dialog(this,user.username,user.email);
    session->get_avatar(user.email,user.avatarmd5);
    if(dialog.exec()==QDialog::Accepted) {
        if(!session->friend_email_list.contains(user.email)){
            QListWidgetItem* item=new QListWidgetItem(ui->listWidget_friends);
            item->setIcon(QPixmap(XMY_Utilities::get_avatar_filename(".cache\\",user.email)));
            item->setText(user.username+'\n'+user.email);
            session->friend_email_list.append(user.email);
            session->friends.append(user);
            session->friend_item.insert(user.email,item);
            session->add_user(user.email);
            slot_friend_list_refreshed();
        }
        else {
            QMessageBox warning(QMessageBox::Warning,"Error","This user has been your friend",QMessageBox::Ok,this);
            warning.exec();
        }
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
    item->setBackground(QColor("white"));
    QStringList info=item->text().split('\n');
    ui->label_email_friend->setText(info[1]);
    ui->label_username_friend->setText(info[0]);
    QPixmap avatar(".cache\\"+XMY_Utilities::emailtomd5(info[1])+".png");
    ui->label_avatar_friend->setPixmap(avatar);
    ui->pushButton_send->setEnabled(true);
    show_messages();
}


void UserMainWindow::on_pushButton_search_clicked()
{
    if(ui->lineEdit_usersearchinput->text().isEmpty() || !XMY_Utilities::check_valid_email(ui->lineEdit_usersearchinput->text())) {
        QMessageBox warning(QMessageBox::Warning,"Error","Please input a valid email",QMessageBox::Ok,this);
        warning.exec();
    }
    else {
        session->search_user(ui->lineEdit_usersearchinput->text());
    }
    ui->lineEdit_usersearchinput->clear();
}

void UserMainWindow::show_messages()
{
    QString email=ui->label_email_friend->text();
    if(email.isEmpty()) return;
    QList<chatMessage> msg;
    msg=session->get_messages_by_email(email);
    ui->listWidget_messages->clear();
    for(auto i:msg) {
        ui->listWidget_messages->addItem(i.time+" - "+i.sender+"\n"+i.msg);

    }
    ui->listWidget_messages->scrollToBottom();
}

