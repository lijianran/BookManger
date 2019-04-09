#include "cdatabase.h"

CDataBase::CDataBase(QObject *parent) : QObject(parent)
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        m_database = QSqlDatabase::database("qt_sql_default_connection");
    else
        m_database = QSqlDatabase::addDatabase("QSQLITE");

    m_checkTables = false;

    connectDB("database.db");
}

bool CDataBase::RegisterUser(User user)
{
    //connectDB("database.db");
    openDataBase();
    QSqlQuery query;
    QString str = "select count(*) from users where stuid='"+user.stuid+"';";
    query.exec(str);
    query.next();
    int n=query.value(0).toInt();
    if(n == 1)
    {
        emit signal_Message(FAILURE_REGISTER_REPEAT);
        return false;
    }
    query.prepare("insert into users (stuid, name, sex, depno, depname, grade, class, tel, addr, pwds)"
                  "values(:stuid, :name, :sex, :depno, :depname, :grade, :class, :tel, :addr, :pwds)");
    query.bindValue(":stuid",user.stuid);
    query.bindValue(":name",user.name);
    query.bindValue(":sex",user.sex);
    query.bindValue(":depno",user.depno);
    query.bindValue(":depname",user.depname);
    query.bindValue(":grade",user.grade);
    query.bindValue(":class",user.classnum);
    query.bindValue(":tel",user.tel);
    query.bindValue(":addr",user.addr);
    query.bindValue(":pwds",user.pwds);
    query.exec();

    closeDataBase();
    emit signal_Message(SUCCESS_REGISTER);
    return true;
}

void CDataBase::slot_RegisterBook(Book book)
{
    openDataBase();
    QSqlQuery query;
    QString str = "select count(*) from books where code='"+book.code+"';";
    query.exec(str);
    query.next();
    int n=query.value(0).toInt();
    if(n == 1)
    {
        emit signal_Message(FAILURE_ADDBOOK_REPEAT);
        return;
    }
    query.prepare("insert into books(code, bookname, writer, publisher, buydate, number, isloan)"
                  "values(:code, :bookname, :writer, :publisher, :buydate, :number, :isloan)");
    query.bindValue(":code",book.code);
    query.bindValue(":bookname",book.bookname);
    query.bindValue(":writer",book.writer);
    query.bindValue(":publisher",book.publisher);
    query.bindValue(":buydate",book.buydate);
    query.bindValue(":number",book.number);
    query.bindValue(":isloan",book.isloan);
    query.exec();
    closeDataBase();
    emit signal_Reflesh("recover");
    emit signal_Message(SUCCESS_ADDBOOK);
}

void CDataBase::slot_BorrowBook(Loan loan,QString pwds)
{
    QString stuid = loan.stuid;
    switch (checkUser(stuid,pwds)) {
    case 0:
        emit signal_Message(SUCCESS_CHECKUSER);
        break;
    case 1:
        emit signal_Message(FAILURE_LOANBOOK_PWDS);
        return;
    case 2:
        emit signal_Message(FAILURE_LOANBOOK_NAME);
        return;
    default:
        break;
    }

    openDataBase();
    QSqlQuery query;
    query.exec("select count(*) from books where code='"+loan.code+"';");
    query.next();
    int n=query.value(0).toInt();
    if(n == 0)
    {
        emit signal_Message(FAILURE_LOANBOOK_NOTEXIST);
        return;
    }

    query.exec("select isloan from books where code = '"+loan.code+"';");
    query.next();
    if(query.value(0).toInt() == 1)
    {
        emit signal_Message(FAILURE_LOANBOOK_LOANED);
        return;
    }

    query.prepare("insert into userbook"
                  "(stuid, code, loandate, returndate)"
                  "values(:stuid, :code, :loandate, :returndate)");
    query.bindValue(":stuid",loan.stuid);
    query.bindValue(":code",loan.code);
    query.bindValue(":loandate",loan.loandate);
    query.bindValue(":returndate",loan.returndate);
    query.exec();

    query.exec("update books set number = number+1 where code = '"+loan.code+"';");
    query.exec("update books set isloan = '1' where code = '"+loan.code+"';");

    closeDataBase();
    emit signal_Reflesh("library");
    emit signal_Message(SUCCESS_LOANBOOK);
}

void CDataBase::slot_RecoverBook(Book book)
{
    openDataBase();
    QSqlQuery query;
    query.exec("delete from books where code = '"+book.code+"';");
    closeDataBase();
    emit signal_Reflesh("recover");
    emit signal_Message(SUCCESS_RECOVER);
}

void CDataBase::slot_ReturnBook(QString code,QString stuid)
{
    openDataBase();
    QSqlQuery query;

    query.exec("select count(*) from userbook where code = '"+code+"' and stuid = '"+stuid+"';");
    query.next();
    if(query.value(0).toInt() == 0)
    {
        emit signal_Message(FAILURE_RETURNBOOK);
        return;
    }

    query.exec("delete from userbook where code = '"+code+"';");
    query.exec("update books set isloan = '0' where code = '"+code+"';");

    closeDataBase();
    emit signal_Reflesh("library");
    emit signal_Message(SUCCESS_RETURNBOOK);
}

bool CDataBase::CheckUser(QString stuid,QString pwds)
{
    switch (checkUser(stuid,pwds)) {
    case 0:
        emit signal_Message(SUCCESS_CHECKUSER);
        return true;
    case 1:
        emit signal_Message(FAILURE_CHECKUSER_PWDS);
        return false;
    case 2:
        emit signal_Message(FAILURE_CHECKUSER_NAME);
        return false;
    default:
        return true;
    }
}

void CDataBase::GetBooks(QList<Book> &books)
{
    openDataBase();
    QSqlQuery query;
    query.exec("select * from books;");
    while(query.next())
    {
        Book book;
        book.code = query.value(0).toString();
        book.bookname = query.value(1).toString();
        book.writer = query.value(2).toString();
        book.publisher = query.value(3).toString();
        book.buydate = query.value(4).toString();
        book.number = query.value(5).toString().toInt();
        if(query.value(6).toString() == "1")
            book.isloan = true;
        else
            book.isloan = false;
        books.push_back(book);
    }
    closeDataBase();
}

void CDataBase::GetUserData(QString stuid, User &user,QList<Loan> &borrowedbook)
{
    openDataBase();
    QSqlQuery query;
    query.exec("select * from users where stuid='"+stuid+"';");

    query.next();
    user.stuid = query.value(0).toString();
    user.name = query.value(1).toString();
    user.sex = query.value(2).toString();
    user.depno = query.value(3).toString();
    user.depname = query.value(4).toString();
    user.grade = query.value(5).toString();
    user.classnum = query.value(6).toString();
    user.tel = query.value(7).toString();
    user.addr = query.value(8).toString();
    user.pwds = query.value(9).toString();

    query.exec("select * from userbook where stuid='"+stuid+"';");
    while(query.next())
    {
        Loan book;
        book.stuid = query.value(0).toString();
        book.code = query.value(1).toString();
        book.loandate = query.value(2).toString();
        book.returndate = query.value(3).toString();
        borrowedbook.push_back(book);
    }
    closeDataBase();
}

int CDataBase::checkUser(QString stuid, QString pwds)
{
    openDataBase();
    QSqlQuery query;
    query.exec("select stuid from users;");
    while(query.next())
    {
        if(query.value(0).toString() == stuid)
        {
            query.exec("select pwds from users where stuid='"+stuid+"';");
            query.next();
            if(query.value(0).toString() == pwds)
            {//成功登录
                m_username = stuid;
                m_userpwds = pwds;
                closeDataBase();
                return 0;
            }
            else
            {//密码错误
                closeDataBase();
                return 1;
            }
        }
    }
    //用户名不存在
    closeDataBase();
    return 2;
}

bool CDataBase::connectDB(QString db_name)
{
    m_database.setDatabaseName(db_name);
    if(m_checkTables)
        return true;
    else
        checkTables("database.db");
    return false;
}

void CDataBase::checkTables(QString db_name)
{
    if(db_name != "database.db")
        return;
    openDataBase();
    if(!m_database.tables().contains("users"))
    {
        QSqlQuery query;
        query.exec("CREATE TABLE users"
                   "(stuid VARCHAR(20) PRIMARY KEY,"
                   "name VARCHAR(10),"
                   "sex VARCHAR(4),"
                   "depno VARCHAR(4),"
                   "depname VARCHAR(20),"
                   "grade VARCHAR(10),"
                   "class VARCHAR(10),"
                   "tel VARCHAR(12),"
                   "addr VARCHAR(50),"
                   "pwds VARCHAR(20))");
    }

    if(!m_database.tables().contains("books"))
    {
        QSqlQuery query;
        query.exec("CREATE TABLE books"
                   "(code VARCHAR(20),"
                   "bookname VARCHAR(50),"
                   "writer VARCHAR(10),"
                   "publisher VARCHAR(50),"
                   "buydate VARCHAR(30),"
                   "number INTEGER,"
                   "isloan INTEGER,"
                   "PRIMARY KEY(code))");
    }

    if(!m_database.tables().contains("userbook"))
    {
        QSqlQuery query;
        query.exec("PRAGMA foreign_keys=ON;");
        query.exec("CREATE TABLE userbook"
                   "(stuid VARCHAR(20),"
                   "code VARCHAR(20),"
                   "loandate VARCHAR(30),"
                   "returndate VARCHAR(30),"
                   "FOREIGN KEY (stuid) REFERENCES users(stuid),"
                   "FOREIGN KEY (code) REFERENCES books(code),"
                   "PRIMARY KEY(stuid,code))");

        m_checkTables = true;
    }
    closeDataBase();
}

bool CDataBase::openDataBase()
{
    if (!m_database.open()) {

        return false;
    }
    return true;
}

bool CDataBase::closeDataBase()
{
    if(!m_database.isOpen())
        return false;
    else
        m_database.close();
    return true;
}
