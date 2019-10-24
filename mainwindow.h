#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "newvisitwindow.h"
#include "newvisitwindow.h"
#include "representative.h"
#include "admin.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Representative *getCurrentRepres();
    void addVisit();

signals:
    void addVisitButton_clicked();

private slots:
    void on_showPasswordButton_pressed();
    void on_showPasswordButton_released();
    void on_loginButton_clicked();
    void on_createNewRepresentative_clicked();
    void on_backButton_clicked();
    void on_represInfoButton_clicked();
    void on_passwordLineEdit_returnPressed();
    void on_loginLineEdit_returnPressed();
    void on_createButton_clicked();
    void on_represAddNewVisitButton_clicked();
    void on_represViewVisitsButton_clicked();
    void on_tableAddNewVisitButton_clicked();
    void on_tableBackButton_clicked();
    void on_represStatBackButton_clicked();
    void on_represSignOutButton_clicked();
    void recieveNewVisit(QString newOrganizationName,
                         QString newFullName,
                         QString newCurrentPosition,
                         QString newSpecialization,
                         QString newData);
    void on_adminSignOutButton_clicked();
    void on_adminShowRepresButton_clicked();
    void on_adminMyRepresBackButton_clicked();
    void on_adminMyRepresOpenButton_clicked();
    void on_admiMyRepresBackButton_clicked();
    void on_adminMyRepresAddNewVisitButton_clicked();
    void on_adminMyRepresViewVisitsButton_clicked();
    void on_tableDeleteCurrentButton_clicked();
    void on_represInfoBackButton_clicked();
    void on_adminMyRepresInfoButton_clicked();
    void on_represInfoBackButton_2_clicked();
    void on_adminInfoButton_clicked();

private:
    Ui::MainWindow *ui;
    NewVisitWindow *visitWnd;
    QSqlDatabase db;
    QSqlTableModel* model;

    Representative *currentRepres;
    Admin *currentAdmin;

    bool adminFlag = false;
};

#endif // MAINWINDOW_H
