#ifndef CUSERREGISTERDIALOG_H
#define CUSERREGISTERDIALOG_H

#include <QDialog>
#include "cheaders.h"

namespace Ui {
class CUserRegisterDialog;
}

class CUserRegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CUserRegisterDialog(QWidget *parent = nullptr);
    ~CUserRegisterDialog();

protected:
    User m_user;
    QButtonGroup *m_pButtonGroup;


public:
    User GetUser();


private slots:

    void on_pushButton_Confirm_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::CUserRegisterDialog *ui;
};

#endif // CUSERREGISTERDIALOG_H
