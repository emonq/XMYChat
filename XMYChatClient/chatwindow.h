#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "../XMYChatShare/xmy_basic.h"
#include "../XMYChatShare/xmy_tcpsocket.h"
#include "loginsession.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr, loginsession* session = nullptr);
    ~ChatWindow();

private slots:
    void on_pushButton_clicked();
    void slot_logout();
    void slot_receive_message(QString, QString);
    void on_pushButton_send_clicked();

    void on_pushButton_search_clicked();

private:
    Ui::ChatWindow *ui;
    loginsession* session;
};

#endif // CHATWINDOW_H
