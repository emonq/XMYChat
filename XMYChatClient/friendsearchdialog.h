#ifndef FRIENDSEARCHDIALOG_H
#define FRIENDSEARCHDIALOG_H

#include <QDialog>

#include "../XMYChatShare/xmy_utilities.h"

namespace Ui {
class FriendSearchDialog;
}

class FriendSearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FriendSearchDialog(QWidget *parent = nullptr, QString username=QString(), QString email=QString());
    ~FriendSearchDialog();

private:
    Ui::FriendSearchDialog *ui;
};

#endif // FRIENDSEARCHDIALOG_H
