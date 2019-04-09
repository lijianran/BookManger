#ifndef CBOOKREGISTERDIALOG_H
#define CBOOKREGISTERDIALOG_H

#include <QDialog>
#include "cheaders.h"

namespace Ui {
class CBookRegisterDialog;
}

class CBookRegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CBookRegisterDialog(QWidget *parent = 0);
    ~CBookRegisterDialog();

public:
    void SetBooksList(QList<Book>);

signals:
    void signal_RegisterBook(Book);
    void signal_RecoverBook(Book);

private slots:
    void on_pushButton_confirm_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_clear_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_detel_clicked();

    void on_pushButton_today_clicked();

private:
    Ui::CBookRegisterDialog *ui;
};

#endif // CBOOKREGISTERDIALOG_H
