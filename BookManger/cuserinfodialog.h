#ifndef CUSERINFODIALOG_H
#define CUSERINFODIALOG_H

#include <QDialog>
#include "cheaders.h"

namespace Ui {
class CUserInfoDialog;
}

class CUserInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CUserInfoDialog(QWidget *parent = nullptr);
    ~CUserInfoDialog();

protected:
    QStandardItemModel* model;

public slots:
    void slot_setUserData(User user,QList<Loan> borrowedbooks);

private:
    Ui::CUserInfoDialog *ui;
};

#endif // CUSERINFODIALOG_H
