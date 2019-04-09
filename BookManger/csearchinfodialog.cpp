#include "csearchinfodialog.h"
#include "ui_csearchinfodialog.h"

CSearchInfoDialog::CSearchInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSearchInfoDialog)
{
    ui->setupUi(this);
}

CSearchInfoDialog::~CSearchInfoDialog()
{
    delete ui;
}

void CSearchInfoDialog::on_pushButton_Confirm_clicked()
{
    if(ui->lineEdit_UserName->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入用户名！",QMessageBox::Yes);
        return;
    }
    if(ui->lineEdit_PassWord->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入密码！",QMessageBox::Yes);
        return;
    }
    QString name = ui->lineEdit_UserName->text();
    QString pwds  = ui->lineEdit_PassWord->text();
    emit signal_Confirm(name,pwds);
    ui->lineEdit_UserName->clear();
    ui->lineEdit_PassWord->clear();
    ui->lineEdit_UserName->setFocus();
}

void CSearchInfoDialog::on_pushButton_Register_clicked()
{
    ui->lineEdit_UserName->clear();
    ui->lineEdit_PassWord->clear();
    ui->lineEdit_UserName->setFocus();
    emit signal_Register();
}

void CSearchInfoDialog::on_pushButton_Cancel_clicked()
{
    reject();
}
