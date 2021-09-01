#ifndef FRIENDSEARCHDIALOG_H
#define FRIENDSEARCHDIALOG_H

#include <QDialog>

#include "../XMYChatShare/xmy_utilities.h"
#include "loginsession.h"

namespace Ui {
class FriendSearchDialog;
}

class FriendSearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FriendSearchDialog(loginsession *session, QWidget *parent = nullptr, QString username=QString(), QString email=QString());
    ~FriendSearchDialog();

private:
    Ui::FriendSearchDialog *ui;
    QString email;

private slots:
    void refresh_avatar(QString email);
};

#endif // FRIENDSEARCHDIALOG_H
