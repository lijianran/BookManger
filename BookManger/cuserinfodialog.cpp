#include "cuserinfodialog.h"
#include "ui_cuserinfodialog.h"

CUserInfoDialog::CUserInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CUserInfoDialog)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    /*设置列字段名*/
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal, "书号");
    model->setHeaderData(1,Qt::Horizontal, "借阅日期");
    model->setHeaderData(2,Qt::Horizontal, "归还日期");
    model->setHeaderData(3,Qt::Horizontal, "状态");

//    ui->UserInfoView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    /*设置行字段名*/
//    model->setRowCount(3);
//    model->setHeaderData(0,Qt::Vertical, "记录一");
//    model->setHeaderData(1,Qt::Vertical, "记录二");
//    model->setHeaderData(2,Qt::Vertical, "记录三");
    /*设置一条数据*/
//    model->setItem(0, 0, new QStandardItem(""));
//    model->setItem(0, 1, new QStandardItem(""));
//    model->setItem(0, 2, new QStandardItem(""));

//    ui->UserInfoView->setModel(model);
}

CUserInfoDialog::~CUserInfoDialog()
{
    delete ui;
}

void CUserInfoDialog::slot_setUserData(User user,QList<Loan> borrowedbooks)
{
    ui->label_addr->setText(user.addr);
    ui->label_class->setText(user.classnum);
    ui->label_depname->setText(user.depname);
    ui->label_grade->setText(user.grade);
    ui->label_name->setText(user.name);
    ui->label_sex->setText(user.sex);
    ui->label_stuid->setText(user.stuid);
    ui->label_tel->setText(user.tel);

    for(int i=0;i<borrowedbooks.size();i++)
    {
        Loan book = borrowedbooks[i];
        model->setItem(i, 0, new QStandardItem(book.code));
        model->setItem(i, 1, new QStandardItem(book.loandate));
        model->setItem(i, 2, new QStandardItem(book.returndate));
        QDateTime return_date = QDateTime::fromString(book.returndate, "yyyy-MM-dd");
        QString restday = QString::number(QDateTime::currentDateTime().daysTo(return_date));
        model->setItem(i, 3, new QStandardItem("借阅时间剩"+restday+"天"));
    }
    ui->UserInfoView->setModel(model);
}
