#include "csearchbookdialog.h"
#include "ui_csearchbookdialog.h"

CSearchBookDialog::CSearchBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSearchBookDialog)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(6); //设置列数
    QStringList header;
    header<<"书籍编号"<<"书籍名称"<<"作者"<<"出版社"/*<<"购买日期"*/<<"借阅次数"<<"是否借出";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->toolBox->setCurrentIndex(0);


}

CSearchBookDialog::~CSearchBookDialog()
{
    delete ui;
}

void CSearchBookDialog::SetBooksList(QList<Book> books)
{
    ui->tableWidget->setRowCount(int(books.size())); //设置行数
    for(int i=0;i<books.size();i++)
    {
        Book book = books[i];
        ui->tableWidget->setItem(int(i),0,new QTableWidgetItem(book.code));
        ui->tableWidget->setItem(int(i),1,new QTableWidgetItem(book.bookname));
        ui->tableWidget->setItem(int(i),2,new QTableWidgetItem(book.writer));
        ui->tableWidget->setItem(int(i),3,new QTableWidgetItem(book.publisher));
        //ui->tableWidget->setItem(i,4,new QTableWidgetItem(book.buydate));
        ui->tableWidget->setItem(int(i),4,new QTableWidgetItem(QString::number(book.number)));
        if(book.isloan)
            ui->tableWidget->setItem(int(i),5,new QTableWidgetItem("是"));
        else
            ui->tableWidget->setItem(int(i),5,new QTableWidgetItem("否"));
    }
}

void CSearchBookDialog::on_pushButton_borrow_clicked()
{
    if(ui->lineEdit_code->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入书籍编号！",QMessageBox::Yes);
        return;
    }
    if(ui->lineEdit_stuid->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入学号！",QMessageBox::Yes);
        return;
    }
    if(ui->lineEdit_pwds->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入密码！",QMessageBox::Yes);
        return;
    }

    int day = ui->spinBox->value();
    QDateTime current_time = QDateTime::currentDateTime();
    QDateTime return_time = QDateTime::currentDateTime().addDays(day);
    Loan loan;
    loan.code = ui->lineEdit_code->text();
    loan.stuid = ui->lineEdit_stuid->text();
    loan.loandate = current_time.toString("yyyy-MM-dd");
    loan.returndate = return_time.toString("yyyy-MM-dd");

    emit signal_BorrowBook(loan,ui->lineEdit_pwds->text());
}

void CSearchBookDialog::on_pushButton_return_clicked()
{
    if(ui->lineEdit_returncode->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入书籍编号！",QMessageBox::Yes);
        return;
    }
    if(ui->lineEdit_returnstuid->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入学号！",QMessageBox::Yes);
        return;
    }
    emit signal_ReturnBook(ui->lineEdit_returncode->text(),ui->lineEdit_returnstuid->text());
    ui->lineEdit_returncode->clear();
    ui->lineEdit_returnstuid->clear();
}
