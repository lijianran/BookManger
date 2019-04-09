#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cheaders.h"
#include "cdatabase.h"
#include "csearchinfodialog.h"
#include "csearchbookdialog.h"
#include "cuserinfodialog.h"
#include "cuserregisterdialog.h"
#include "cbookregisterdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    CDataBase *m_DataBase;
    CSearchInfoDialog *m_dialog_SearchInfo;
    CSearchBookDialog *m_dialog_SearchBook;
    CUserRegisterDialog *m_dialog_RegisterUser;
    CUserInfoDialog *m_dialog_UserInfomation;
    CBookRegisterDialog *m_dialog_RegisterBook;


protected slots:
    void slot_Message(Message);
    void slot_RegisterUser();
    void slot_CheckUser(QString,QString);

    void slot_setRecoverBooks();
    void slot_setUserData(QString);
    void slot_setLibraryBooks();

    void slot_Reflesh(QString);

private slots:
    void on_pushButton_SearchInfo_clicked();

    void on_pushButton_SearchBook_clicked();

    void on_pushButton_ManageBooks_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
