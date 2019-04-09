#ifndef CHEADERS_H
#define CHEADERS_H

#include <QMessageBox>
#include <QStandardItemModel>
#include <QDateTime>
#include <QFile>
#include <QMouseEvent>
#include <QRegExp>
#include <QRegExpValidator>
#include <QIntValidator>
#include <QButtonGroup>
#include <QRect>


typedef struct _User_Type
{
    QString stuid;
    QString name;
    QString sex;
    QString depno;
    QString depname;
    QString grade;
    QString classnum;
    QString tel;
    QString addr;
    QString pwds;

}User;

typedef struct _Book_Type
{
    QString code;
    QString bookname;
    QString writer;
    QString publisher;
    QString buydate;
    int number;
    bool isloan;

}Book;

typedef struct _Borrow_Info_Type
{
    QString code;
    QString stuid;
    QString loandate;
    QString returndate;

}Loan;

typedef enum _Message_Type
{
    SUCCESS_REGISTER,
    FAILURE_REGISTER_REPEAT,

    SUCCESS_CHECKUSER,
    FAILURE_CHECKUSER_NAME,
    FAILURE_CHECKUSER_PWDS,

    SUCCESS_ADDBOOK,
    FAILURE_ADDBOOK_REPEAT,

    SUCCESS_LOANBOOK,
    FAILURE_LOANBOOK_LOANED,
    FAILURE_LOANBOOK_NOTEXIST,
    FAILURE_LOANBOOK_NAME,
    FAILURE_LOANBOOK_PWDS,

    SUCCESS_RECOVER,

    SUCCESS_RETURNBOOK,
    FAILURE_RETURNBOOK,

}Message;

typedef enum _BooksList_Type
{
    LIBRARY,
    BORROWED,
    RECOVERY

}BookList;

#endif // CHEADERS_H
