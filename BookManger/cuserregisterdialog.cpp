#include "cuserregisterdialog.h"
#include "ui_cuserregisterdialog.h"

CUserRegisterDialog::CUserRegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CUserRegisterDialog)
{
    ui->setupUi(this);

    QRegExp numbertype("^[0-9]*$");
    QRegExpValidator *number = new QRegExpValidator(numbertype,this);
    ui->lineEdit_stuid->setValidator(number);
    ui->lineEdit_depno->setValidator(number);
    ui->lineEdit_tel->setValidator(number);
    QRegExp chinesetype("^[\u4e00-\u9fa5]{0,}$");
    QRegExpValidator *chinese = new QRegExpValidator(chinesetype,this);
    ui->lineEdit_name->setValidator(chinese);
    ui->lineEdit_depname->setValidator(chinese);


    m_pButtonGroup = new QButtonGroup(this);
    m_pButtonGroup->setExclusive(true);
    m_pButtonGroup->addButton(ui->radioButton_man);
    m_pButtonGroup->addButton(ui->radioButton_woman);
    ui->radioButton_man->setChecked(true);

    for(int i=0;i<30;i++)
        ui->comboBox_class->addItem(QString::number(i+1));

    QString current_year = QDateTime::currentDateTime().toString("yyyy");
    int year = current_year.toInt();
    for(int i=0;i<5;i++)
    {
        ui->comboBox_grade->addItem(QString::number(year));
        year--;
    }
}

CUserRegisterDialog::~CUserRegisterDialog()
{
    delete ui;
}

void CUserRegisterDialog::on_pushButton_Confirm_clicked()
{
    if(ui->lineEdit_addr->text().isEmpty() ||
            ui->lineEdit_depname->text().isEmpty() ||
            ui->lineEdit_depno->text().isEmpty() ||
            ui->lineEdit_name->text().isEmpty() ||
            ui->lineEdit_stuid->text().isEmpty() ||
            ui->lineEdit_tel->text().isEmpty() ||
            ui->lineEdit_password->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","输入不能为空",QMessageBox::Yes);
        return;
    }
    m_user.addr = ui->lineEdit_addr->text();
    m_user.classnum = ui->comboBox_class->currentText();
    m_user.depname = ui->lineEdit_depname->text();
    m_user.depno = ui->lineEdit_depno->text();
    m_user.grade = ui->comboBox_grade->currentText();
    m_user.name  = ui->lineEdit_name->text();
    m_user.sex = (m_pButtonGroup->checkedId()==-2?"男":"女");
    m_user.stuid = ui->lineEdit_stuid->text();
    m_user.tel = ui->lineEdit_tel->text();
    m_user.pwds = ui->lineEdit_password->text();
    accept();
}

void CUserRegisterDialog::on_pushButton_Cancel_clicked()
{
    reject();
}

User CUserRegisterDialog::GetUser()
{
    return m_user;
}

