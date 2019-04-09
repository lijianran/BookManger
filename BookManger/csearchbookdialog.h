#ifndef CSEARCHBOOKDIALOG_H
#define CSEARCHBOOKDIALOG_H

#include <QDialog>
#include "cheaders.h"

namespace Ui {
class CSearchBookDialog;
}

class CSearchBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CSearchBookDialog(QWidget *parent = nullptr);
    ~CSearchBookDialog();

public:
    void SetBooksList(QList<Book>);


signals:
    void signal_BorrowBook(Loan,QString);
    void signal_ReturnBook(QString,QString);

private slots:
    void on_pushButton_borrow_clicked();

    void on_pushButton_return_clicked();

private:
    Ui::CSearchBookDialog *ui;
};

#endif // CSEARCHBOOKDIALOG_H
