#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>

#include "../XMYChatShare/xmy_basic.h"
#include "userinfodialog.h"
#include "loginsession.h"
#include "friendsearchdialog.h"

namespace Ui {
class UserMainWindow;
}

class UserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserMainWindow(QWidget *parent = nullptr, loginsession* session=nullptr);
    ~UserMainWindow();

private slots:
    void slot_logout();
    void slot_receive_message(chatMessage);
    void on_pushButton_send_clicked();
    void slot_info_refresh();
    void slot_friend_list_refreshed();
    void slot_avatar_got(QString email);
    void slot_user_found(userStruct user);
    void on_pushButton_logout_clicked();
    void on_pushButton_editinfo_clicked();
    void on_listWidget_friends_itemClicked(QListWidgetItem *item);
    void on_pushButton_search_clicked();
    void show_messages();
    bool eventFilter(QObject* object, QEvent* event);

    void on_listWidget_friends_customContextMenuRequested(const QPoint &pos);
    void deleteSeedSlot();

private:
    Ui::UserMainWindow *ui;
    loginsession* session;

    void fill_user_info();
    void clear_friend_info();
};

#endif // USERMAINWINDOW_H
