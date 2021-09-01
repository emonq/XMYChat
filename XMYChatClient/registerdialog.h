#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "loginsession.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(loginsession* session, QWidget *parent = nullptr, QString email=QString(), QString password=QString());
    ~RegisterDialog();

private:
    Ui::RegisterDialog *ui;
    loginsession* session;

    bool check_form();
    void set_status(bool status);

private slots:
    void register_callback(int result);
    void on_pushButton_send_code_clicked();
    void on_pushButton_register_clicked();
};

#endif // REGISTERDIALOG_H
