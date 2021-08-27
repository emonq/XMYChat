#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class settingDialog;
}

class settingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit settingDialog(QWidget *parent = nullptr, QString ip="127.0.0.1", int port=42000);
    ~settingDialog();
    QString get_ip();
    int get_port();

private:
    Ui::settingDialog *ui;
};

#endif // SETTINGDIALOG_H
