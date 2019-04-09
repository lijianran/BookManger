#ifndef CDATABASE_H
#define CDATABASE_H

#include <QObject>
#include "cheaders.h"

#include <QSqlDatabase>
#include <QSqlQuery>

class CDataBase : public QObject
{
    Q_OBJECT
public:
    explicit CDataBase(QObject *parent = nullptr);

protected:
    QSqlDatabase m_database;
    QString m_username;
    QString m_userpwds;
    QString m_database_name;
    bool m_checkTables;

public:
    bool RegisterUser(User user);
    bool CheckUser(QString stuid, QString pwds);
    void GetBooks(QList<Book> &);
    void GetUserData(QString, User &, QList<Loan> &);

protected:
    bool connectDB(QString db_name);
    void checkTables(QString db_name);
    bool openDataBase();
    bool closeDataBase();

    int checkUser(QString stuid, QString pwds);

signals:
    void signal_Message(Message);
    void signal_Reflesh(QString);

public slots:
    void slot_RegisterBook(Book);
    void slot_BorrowBook(Loan,QString);
    void slot_RecoverBook(Book);
    void slot_ReturnBook(QString,QString);

};

#endif // CDATABASE_H
