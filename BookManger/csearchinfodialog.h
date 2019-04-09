#ifndef CSEARCHINFODIALOG_H
#define CSEARCHINFODIALOG_H

#include <QDialog>
#include "cheaders.h"


namespace Ui {
class CSearchInfoDialog;
}

class CSearchInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CSearchInfoDialog(QWidget *parent = nullptr);
    ~CSearchInfoDialog();

signals:
    void signal_Confirm(QString,QString);
    void signal_Register();

private slots:
    void on_pushButton_Confirm_clicked();

    void on_pushButton_Register_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::CSearchInfoDialog *ui;
};

#endif // CSEARCHINFODIALOG_H
