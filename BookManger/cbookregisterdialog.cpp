#include "cbookregisterdialog.h"
#include "ui_cbookregisterdialog.h"

CBookRegisterDialog::CBookRegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CBookRegisterDialog)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);

    ui->tableWidget->setColumnCount(7); //设置列数
    QStringList header;
    header<<"书籍编号"<<"书籍名称"<<"作者"<<"出版社"<<"购买日期"<<"借阅次数"<<"是否借阅";
    ui->tableWidget->setHorizontalHeaderLabels(header);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->lineEdit_ID->setText("admin");
    ui->lineEdit_Pwds->setText("admin");

//    Qt::WindowFlags flags = Qt::Dialog;
//     flags |= Qt::WindowMinMaxButtonsHint;
//     flags |= Qt::WindowCloseButtonHint;
//     setWindowFlags(flags);

}

CBookRegisterDialog::~CBookRegisterDialog()
{
    delete ui;
}

void CBookRegisterDialog::SetBooksList(QList<Book> books)
{
    ui->tableWidget->setRowCount(int(books.size())); //设置行数
    for(int i=0;i<books.size();i++)
    {
        Book book = books[i];
        int j = int(i);
        ui->tableWidget->setItem(j,0,new QTableWidgetItem(book.code));
        ui->tableWidget->setItem(j,1,new QTableWidgetItem(book.bookname));
        ui->tableWidget->setItem(j,2,new QTableWidgetItem(book.writer));
        ui->tableWidget->setItem(j,3,new QTableWidgetItem(book.publisher));
        ui->tableWidget->setItem(j,4,new QTableWidgetItem(book.buydate));
        ui->tableWidget->setItem(j,5,new QTableWidgetItem(QString::number(book.number)));
        if(book.isloan)
            ui->tableWidget->setItem(j,6,new QTableWidgetItem("是"));
        else
            ui->tableWidget->setItem(j,6,new QTableWidgetItem("否"));
    }
}

void CBookRegisterDialog::on_pushButton_confirm_clicked()
{
    if(ui->lineEdit_ID->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入用户名！",QMessageBox::Yes);
        return;
    }
    if(ui->lineEdit_Pwds->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入密码",QMessageBox::Yes);
        return;
    }
    QString name = ui->lineEdit_ID->text();
    QString pwds = ui->lineEdit_Pwds->text();
    if(name != "admin")
    {
        QMessageBox::warning(this,"警告","用户名错误!",QMessageBox::Yes);
        return;
    }
    if(pwds != "admin")
    {
        QMessageBox::warning(this,"警告","密码错误!",QMessageBox::Yes);
        return;
    }
    int nIndex = ui->stackedWidget->currentIndex();
    nIndex--;
    ui->stackedWidget->setCurrentIndex(nIndex);
    ui->tabWidget->setCurrentIndex(0);
    ui->lineEdit_code->setFocus();
}

void CBookRegisterDialog::on_pushButton_cancel_clicked()
{
    ui->lineEdit_ID->clear();
    ui->lineEdit_Pwds->clear();
    reject();
}

void CBookRegisterDialog::on_pushButton_add_clicked()
{
    if(ui->lineEdit_code->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入书籍编号！",QMessageBox::Yes);
        return;
    }
    if(ui->lineEdit_bookname->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入书籍名称！",QMessageBox::Yes);
        return;
    }
    if(ui->lineEdit_writer->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入作者！",QMessageBox::Yes);
        return;
    }
    if(ui->lineEdit_publisher->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入出版社！",QMessageBox::Yes);
        return;
    }
    if(ui->lineEdit_buydate->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入购买日期！",QMessageBox::Yes);
        return;
    }
    Book book;
    book.code = ui->lineEdit_code->text();
    book.bookname = ui->lineEdit_bookname->text();
    book.writer = ui->lineEdit_writer->text();
    book.publisher = ui->lineEdit_publisher->text();
    book.buydate = ui->lineEdit_buydate->text();
    book.number = 0;
    book.isloan = false;
    emit signal_RegisterBook(book);
}

void CBookRegisterDialog::on_pushButton_clear_clicked()
{
    ui->lineEdit_code->clear();
    ui->lineEdit_bookname->clear();
    ui->lineEdit_writer->clear();
    ui->lineEdit_publisher->clear();
    ui->lineEdit_buydate->clear();
}

void CBookRegisterDialog::on_tabWidget_currentChanged(int index)
{
    if(index == 0)
        ui->pushButton_add->setFocus();
    if(index == 1)
        ui->pushButton_detel->setFocus();
}

void CBookRegisterDialog::on_pushButton_detel_clicked()
{
    int current_row = ui->tableWidget->currentRow();
    if(current_row == -1)
    {
        QMessageBox::warning(this,"提示","请选中一行！",QMessageBox::Yes);
        return;
    }
    if(ui->tableWidget->item(current_row,6)->text() == "是")
    {
        QMessageBox::warning(this,"警告","此书籍已被借阅，无法回收！",QMessageBox::Yes);
        return;
    }

    if(QMessageBox::warning(this,"警告","是否收回书籍《"+ui->tableWidget->item(current_row,1)->text()+"》"
                            ,QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
    {
        Book book;
        book.code = ui->tableWidget->item(current_row,0)->text();
        book.bookname = ui->tableWidget->item(current_row,1)->text();
        book.writer = ui->tableWidget->item(current_row,2)->text();
        book.publisher = ui->tableWidget->item(current_row,3)->text();
        book.buydate = ui->tableWidget->item(current_row,4)->text();
        book.number = ui->tableWidget->item(current_row,5)->text().toInt();
        book.isloan = false;
        emit signal_RecoverBook(book);
    }
}

void CBookRegisterDialog::on_pushButton_today_clicked()
{
    ui->lineEdit_buydate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
}
