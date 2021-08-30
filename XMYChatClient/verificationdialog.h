#ifndef VERIFICATIONDIALOG_H
#define VERIFICATIONDIALOG_H

#include <QDialog>

namespace Ui {
class VerificationDialog;
}

class VerificationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VerificationDialog(QWidget *parent = nullptr);
    int get_code();
    ~VerificationDialog();

private:
    Ui::VerificationDialog *ui;
};

#endif // VERIFICATIONDIALOG_H
