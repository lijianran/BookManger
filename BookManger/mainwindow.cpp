#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
//    ui->menuBar->hide();
//    ui->statusBar->hide();

    m_dialog_SearchInfo = nullptr;
    m_dialog_SearchBook = nullptr;
    m_dialog_RegisterUser = nullptr;
    m_dialog_UserInfomation = nullptr;
    m_dialog_RegisterBook = nullptr;

    m_DataBase = new CDataBase(this);
    connect(m_DataBase,SIGNAL(signal_Message(Message)),this,SLOT(slot_Message(Message)));
    connect(m_DataBase,SIGNAL(signal_Reflesh(QString)),this,SLOT(slot_Reflesh(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_Message(Message message)
{
    switch (message) {
    case SUCCESS_REGISTER:
        QMessageBox::information(m_dialog_RegisterUser,"提示","注册成功！",QMessageBox::Yes);
        break;
    case FAILURE_REGISTER_REPEAT:
        QMessageBox::warning(m_dialog_RegisterUser,"警告","该用户已注册，本次操作失败！",QMessageBox::Yes);
        break;
    case FAILURE_CHECKUSER_NAME:
        QMessageBox::warning(m_dialog_SearchInfo,"警告","用户名不存在！",QMessageBox::Yes);
        break;
    case FAILURE_CHECKUSER_PWDS:
        QMessageBox::warning(m_dialog_SearchInfo,"警告","密码错误！",QMessageBox::Yes);
        break;
    case SUCCESS_ADDBOOK:
       QMessageBox::information(m_dialog_RegisterBook,"提示","添加书籍成功！",QMessageBox::Yes);
        break;
    case FAILURE_ADDBOOK_REPEAT:
        QMessageBox::warning(m_dialog_RegisterBook,"警告","书籍编号重复，添加失败！",QMessageBox::Yes);
        break;
    case SUCCESS_LOANBOOK:
        QMessageBox::information(m_dialog_SearchBook,"提示","借阅书籍成功！",QMessageBox::Yes);
        break;
    case FAILURE_LOANBOOK_LOANED:
        QMessageBox::warning(m_dialog_SearchBook,"提示","本书已被借阅，本次借阅失败！",QMessageBox::Yes);
        break;
    case FAILURE_LOANBOOK_NOTEXIST:
        QMessageBox::warning(m_dialog_SearchBook,"提示","书号错误，借阅失败！",QMessageBox::Yes);
        break;
    case FAILURE_LOANBOOK_NAME:
        QMessageBox::warning(m_dialog_SearchBook,"警告","学号错误，借阅失败！",QMessageBox::Yes);
        break;
    case FAILURE_LOANBOOK_PWDS:
        QMessageBox::warning(m_dialog_SearchBook,"警告","密码错误，借阅失败！",QMessageBox::Yes);
        break;
    case SUCCESS_RECOVER:
        QMessageBox::information(m_dialog_RegisterBook,"提示","收回成功！",QMessageBox::Yes);
        break;
    case SUCCESS_RETURNBOOK:
        QMessageBox::information(m_dialog_SearchBook,"提示","还书成功！",QMessageBox::Yes);
        break;
    case FAILURE_RETURNBOOK:
        QMessageBox::warning(m_dialog_SearchBook,"提示","还书失败，请检查信息！",QMessageBox::Yes);
        break;
    default:
        break;
    }
}

void MainWindow::slot_RegisterUser()
{
    if(!m_dialog_RegisterUser)
    {
        m_dialog_RegisterUser = new CUserRegisterDialog();
        connect(m_dialog_RegisterUser,SIGNAL(rejected()),m_dialog_SearchInfo,SLOT(show()));
        connect(m_dialog_RegisterUser,SIGNAL(accepted()),this,SLOT(show()));
    }
    m_dialog_SearchInfo->hide();
    if(m_dialog_RegisterUser->exec() == QDialog::Accepted)
    {
        User temp = m_dialog_RegisterUser->GetUser();
        m_DataBase->RegisterUser(temp);
    }
}

void MainWindow::slot_CheckUser(QString stuid,QString pwds)
{
    if(!m_dialog_UserInfomation)
    {
        m_dialog_UserInfomation = new CUserInfoDialog();
        connect(m_dialog_UserInfomation,SIGNAL(rejected()),this,SLOT(show()));
    }
    if(m_DataBase->CheckUser(stuid,pwds))
    {
        m_dialog_SearchInfo->hide();
        slot_setUserData(stuid);
        m_dialog_UserInfomation->show();
    }
}

void MainWindow::slot_setRecoverBooks()
{
    QList<Book> books;
    m_DataBase->GetBooks(books);
    m_dialog_RegisterBook->SetBooksList(books);
}

void MainWindow::slot_setUserData(QString stuid)
{
    User user;
    QList<Loan> borrowedBooks;
    m_DataBase->GetUserData(stuid, user, borrowedBooks);
    m_dialog_UserInfomation->slot_setUserData(user,borrowedBooks);
}

void MainWindow::slot_setLibraryBooks()
{
    QList<Book> books;
    m_DataBase->GetBooks(books);
    m_dialog_SearchBook->SetBooksList(books);
}

void MainWindow::slot_Reflesh(QString code)
{
    if(code == "library")
        slot_setLibraryBooks();
//    if(code == "userdata")
//        slot_setUserData(m_stuid);
    if(code == "recover")
        slot_setRecoverBooks();
}

void MainWindow::on_pushButton_SearchInfo_clicked()
{
    if(!m_dialog_SearchInfo)
    {
        m_dialog_SearchInfo = new CSearchInfoDialog();
        connect(m_dialog_SearchInfo,SIGNAL(signal_Register()),this,SLOT(slot_RegisterUser()));
        connect(m_dialog_SearchInfo,SIGNAL(signal_Confirm(QString,QString)),this,SLOT(slot_CheckUser(QString,QString)));
        connect(m_dialog_SearchInfo,SIGNAL(rejected()),this,SLOT(show()));
    }
    this->hide();
    m_dialog_SearchInfo->show();
}

void MainWindow::on_pushButton_SearchBook_clicked()
{
    if(!m_dialog_SearchBook)
    {
        m_dialog_SearchBook = new CSearchBookDialog();
        connect(m_dialog_SearchBook,SIGNAL(signal_BorrowBook(Loan,QString)),m_DataBase,SLOT(slot_BorrowBook(Loan,QString)));
        connect(m_dialog_SearchBook,SIGNAL(signal_ReturnBook(QString,QString)),m_DataBase,SLOT(slot_ReturnBook(QString,QString)));
        connect(m_dialog_SearchBook,SIGNAL(rejected()),this,SLOT(show()));
    }
    this->hide();
    slot_setLibraryBooks();
    m_dialog_SearchBook->show();
}

void MainWindow::on_pushButton_ManageBooks_clicked()
{
    if(!m_dialog_RegisterBook)
    {
        m_dialog_RegisterBook = new CBookRegisterDialog();
        connect(m_dialog_RegisterBook,SIGNAL(signal_RegisterBook(Book)),m_DataBase,SLOT(slot_RegisterBook(Book)));
        connect(m_dialog_RegisterBook,SIGNAL(signal_RecoverBook(Book)),m_DataBase,SLOT(slot_RecoverBook(Book)));
        connect(m_dialog_RegisterBook,SIGNAL(rejected()),this,SLOT(show()));
    }
    this->hide();
    slot_setRecoverBooks();
    m_dialog_RegisterBook->show();
}


