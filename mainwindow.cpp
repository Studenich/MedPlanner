#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newvisitwindow.h"
#include <QLineEdit>
#include <QDebug>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    ui->loginButton->setAutoDefault(true);
    ui->MainStackedWidget->setCurrentIndex(0);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("MedPlanner.db");
    if (!db.open())
    {
        qDebug() << db.lastError().text();
    }
    else
        qDebug() << "Success.";


    visitWnd = new NewVisitWindow(this);
    currentRepres = new Representative;
    currentAdmin = new Admin;

    connect(visitWnd, SIGNAL(sendNewVisit(QString,QString,QString,QString,QString)),
            this, SLOT(recieveNewVisit(QString,QString,QString,QString,QString)));

    model = new QSqlTableModel(this, db);
    model->setTable("Representatives");
    model->select();
    ui->mainTableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete visitWnd;
    delete currentRepres;
    delete currentAdmin;
    delete model;
}

Representative *MainWindow::getCurrentRepres()
{
    return currentRepres;
}

void MainWindow::on_showPasswordButton_pressed()
{
    ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
}
void MainWindow::on_showPasswordButton_released()
{
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}
void MainWindow::on_loginButton_clicked()
{
    QSqlQuery qry;


    qry.exec("SELECT * FROM Admins");

    while (qry.next())
    {
        if(QString::compare(ui->loginLineEdit->text(), qry.value(0).toString(), Qt::CaseInsensitive) == 0)
        {
            if (QString::compare(ui->passwordLineEdit->text(), qry.value(1).toString(), Qt::CaseSensitive) == 0)
            {
                qDebug() << "Passed! " << qry.value(0).toString();
                ui->mistakeLabel->setStyleSheet("color: rgb(240, 240, 240)");
                ui->loginLineEdit->setText("");
                ui->passwordLineEdit->setText("");
                currentAdmin->setCurrent(qry.value(0).toString());
                adminFlag = true;

                ui->adminHeaderLabel->setText(currentAdmin->getName() +" " +currentAdmin->getSurname()
                                              +" - " +currentAdmin->getOrganization());
                ui->adminInfoButton->setText("Информация о " +currentAdmin->getName() +" " +currentAdmin->getSurname());

                ui->MainStackedWidget->setCurrentIndex(6);


                return;
            }
        }
    }

    qry.exec("SELECT * FROM Representatives");

    while (qry.next())
    {
        if(QString::compare(ui->loginLineEdit->text(), qry.value(0).toString(), Qt::CaseInsensitive) == 0)
        {
            //qDebug() << ui->loginLineEdit->text();
           // qDebug() << "FIND!";
            if (QString::compare(ui->passwordLineEdit->text(), qry.value(1).toString(), Qt::CaseSensitive) == 0)
            {
                qDebug() << "Passed!";
                ui->mistakeLabel->setStyleSheet("color: rgb(240, 240, 240)");
                ui->loginLineEdit->setText("");
                ui->passwordLineEdit->setText("");
                currentRepres->setCurrent(qry.value(0).toString());

                ui->represHeaderLabel->setText(currentRepres->getName() +" " +currentRepres->getSurname()
                                               +" - " +currentRepres->getOrganization());
                ui->represInfoButton->setText("Информация о " +currentRepres->getName() +" " +currentRepres->getSurname());

                ui->MainStackedWidget->setCurrentIndex(3);

                return;
            }
        }
    }

    ui->mistakeLabel->setStyleSheet("color: rgb(255, 80, 80)");
    qDebug() << "Unpassed.";
}
void MainWindow::on_createNewRepresentative_clicked()
{
    ui->MainStackedWidget->setCurrentIndex(1);
}
void MainWindow::on_backButton_clicked()
{
    ui->MainStackedWidget->setCurrentIndex(0);
}
void MainWindow::on_represInfoButton_clicked()
{
    QString temp;

    ui->represInfoSurname->setText(currentRepres->getSurname());
    ui->represInfoName->setText(currentRepres->getName());
    ui->represInfoSex->setText(currentRepres->getSex()==M?"Male":"Female");
    ui->represInfoOrganization->setText(currentRepres->getOrganization());
    ui->represInfoDob->setText(currentRepres->getDob());
    ui->represInfoCountry->setText(currentRepres->getAdress()->getCountry());
    ui->represInfoCity->setText(currentRepres->getAdress()->getCity());
    ui->represInfoStreet->setText(currentRepres->getAdress()->getStreet());
    ui->represInfoHouseNumber->setText(temp.setNum(currentRepres->getAdress()->getHouseNumber()));
    ui->represInfoFlatNumber->setText(temp.setNum(currentRepres->getAdress()->getFlatNumber()));
    ui->represInfoTelephone->setText(currentRepres->getConnections()->getTelephone());
    ui->represInfoEmail->setText(currentRepres->getConnections()->getEmail());

    ui->MainStackedWidget->setCurrentIndex(5);
}
void MainWindow::on_passwordLineEdit_returnPressed()
{
    ui->loginButton->click();
}
void MainWindow::on_loginLineEdit_returnPressed()
{
    ui->loginButton->click();
}
void MainWindow::on_createButton_clicked()
{
    QSqlQuery qry;

    if(QString::compare(ui->newLoginLineEdit->text(), "admin", Qt::CaseInsensitive) == 0)


    qry.exec("SELECT * FROM Representatives");
    qry.prepare("INSERT INTO Representatives(login, password, name, surname, organization, sex, dob, "
                  "country, city, street, houseNumber, flatNumber, email, telephone) "
                  "VALUES (:login,:password,:name,:surname,:organization,:sex,:dob,"
                  ":country,:city,:street,:houseNumber,:flatNumber,:email,:telephone)");

    qry.bindValue(":login",          ui->newLoginLineEdit->text());
    qry.bindValue(":password",       ui->newPasswordLineEdit->text());
    qry.bindValue(":name",           ui->newNameLineEdit->text());
    qry.bindValue(":surname",        ui->newSurnameLineEdit->text());
    qry.bindValue(":organization",   ui->newOrganizationLineEdit->text());
    qry.bindValue(":sex",            ui->newSexLineEdit->text());
    qry.bindValue(":dob",            ui->newDobLineEdit->text());
    qry.bindValue(":country",        ui->newCountryLineEdit->text());
    qry.bindValue(":city",           ui->newCityLineEdit->text());
    qry.bindValue(":street",         ui->newStreetLineEdit->text());
    qry.bindValue(":houseNumber",    ui->newHouseNumberLineEdit->text().toInt());
    qry.bindValue(":flatNumber",     ui->newFlatNumberLineEdit->text().toInt());
    qry.bindValue(":email",          ui->newEmailLineEdit->text());
    qry.bindValue(":telephone",      ui->newTelephoneLineEdit->text().toInt());

    if(!qry.exec())
        qDebug() << "Новый аккаунт не создан";

    QString newTableName = ui->newLoginLineEdit->text();
    qDebug() << newTableName;
    QString str = "CREATE TABLE " +newTableName +" ("
                  "organizationName TEXT, "
                  "fullName TEXT, "
                  "currentPosition TEXT, "
                  "specialization TEXT, "
                  "date TEXT);";

    qry.exec(str);

    ui->MainStackedWidget->setCurrentIndex(0);
}
void MainWindow::on_represAddNewVisitButton_clicked()
{
    visitWnd->show();
}
void MainWindow::on_represViewVisitsButton_clicked()
{
    model = new QSqlTableModel(this, db);
    model->setTable(currentRepres->getLogin());
    model->select();
    ui->mainTableView->setModel(model);

    ui->MainStackedWidget->setCurrentIndex(2);
}
void MainWindow::on_tableAddNewVisitButton_clicked()
{
    visitWnd->show();
}
void MainWindow::on_tableBackButton_clicked()
{
    if(adminFlag)
        ui->MainStackedWidget->setCurrentIndex(8);
    else
        ui->MainStackedWidget->setCurrentIndex(3);
}
void MainWindow::on_represStatBackButton_clicked()
{
    ui->MainStackedWidget->setCurrentIndex(3);
}
void MainWindow::recieveNewVisit(QString newOrganizationName,
                                 QString newFullName,
                                 QString newCurrentPosition,
                                 QString newSpecialization,
                                 QString newData)
{
    QSqlQuery qry;

    qry.exec("SELECT * FROM " +currentRepres->getLogin());
    qDebug() << "SELECTED? - " << qry.isSelect();

        if (
        !qry.prepare("INSERT INTO " +currentRepres->getLogin() +"(organizationName, fullName, "
                    "currentPosition, specialization, date)"
                    "VALUES (:organizationName, :fullName, :currentPosition, :specialization, :date)"))
            qDebug() << "PROBLEM WITH PREPARE";


        qry.bindValue(":organizationName",    newOrganizationName);
        qry.bindValue(":fullName",            newFullName);
        qry.bindValue(":currentPosition",     newCurrentPosition);
        qry.bindValue(":specialization",      newSpecialization);
        qry.bindValue(":date",                newData);

        if(!qry.exec())
            qDebug() << "Ne zapisalos((";

    model->setTable(currentRepres->getLogin());
    model->select();
    ui->mainTableView->setModel(model);
}
void MainWindow::on_represSignOutButton_clicked()
{
    ui->MainStackedWidget->setCurrentIndex(0);
}
void MainWindow::on_adminSignOutButton_clicked()
{
    adminFlag = false;

    ui->MainStackedWidget->setCurrentIndex(0);
}
void MainWindow::on_adminShowRepresButton_clicked()
{
    ui->MainStackedWidget->setCurrentIndex(7);

    model = new QSqlTableModel(this, db);
    model->setTable("Representatives");
    model->select();
    ui->adminMyRepresTableView->setModel(model);
}
void MainWindow::on_adminMyRepresBackButton_clicked()
{
    ui->MainStackedWidget->setCurrentIndex(6);
}
void MainWindow::on_adminMyRepresOpenButton_clicked()
{
    QSqlQuery qry;

    qry.exec("SELECT * FROM Representatives");

    while (qry.next())
    {
        if(QString::compare(ui->adminMyRepresLoginLineEdit->text(), qry.value(0).toString(), Qt::CaseInsensitive) == 0)
        {
            qDebug() << "Passed!";
            ui->adminMyRepresMistakeLabel->setStyleSheet("color: rgb(240, 240, 240)");
            currentRepres->setCurrent(qry.value(0).toString());

            ui->adminMyRepresAdminLabel->setText(currentAdmin->getName() +" " +currentAdmin->getSurname()
                                               +" - " +currentAdmin->getOrganization());
            ui->adminMyRepresRepresLabel->setText(currentRepres->getName() +" " +currentRepres->getSurname());
            ui->adminMyRepresInfoButton->setText("Информация о " +currentRepres->getName() +" " +currentRepres->getSurname());

            ui->MainStackedWidget->setCurrentIndex(8);

            return;
        }
    }

    ui->adminMyRepresMistakeLabel->setStyleSheet("color: rgb(255, 80, 80)");
}
void MainWindow::on_admiMyRepresBackButton_clicked()
{
    ui->MainStackedWidget->setCurrentIndex(7);
}
void MainWindow::on_adminMyRepresAddNewVisitButton_clicked()
{
    visitWnd->show();
}
void MainWindow::on_adminMyRepresViewVisitsButton_clicked()
{
    model = new QSqlTableModel(this, db);
    model->setTable(currentRepres->getLogin());
    model->select();
    ui->mainTableView->setModel(model);

    ui->MainStackedWidget->setCurrentIndex(2);
}
void MainWindow::on_tableDeleteCurrentButton_clicked()
{
    model->removeRow(ui->mainTableView->currentIndex().row());
}
void MainWindow::on_represInfoBackButton_clicked()
{
    if(adminFlag)
        ui->MainStackedWidget->setCurrentIndex(8);
    else
        ui->MainStackedWidget->setCurrentIndex(3);
}
void MainWindow::on_adminMyRepresInfoButton_clicked()
{
    QString temp;

    ui->represInfoSurname->setText(currentRepres->getSurname());
    ui->represInfoName->setText(currentRepres->getName());
    ui->represInfoSex->setText(currentRepres->getSex()==M?"Male":"Female");
    ui->represInfoOrganization->setText(currentRepres->getOrganization());
    ui->represInfoDob->setText(currentRepres->getDob());
    ui->represInfoCountry->setText(currentRepres->getAdress()->getCountry());
    ui->represInfoCity->setText(currentRepres->getAdress()->getCity());
    ui->represInfoStreet->setText(currentRepres->getAdress()->getStreet());
    ui->represInfoHouseNumber->setText(temp.setNum(currentRepres->getAdress()->getHouseNumber()));
    ui->represInfoFlatNumber->setText(temp.setNum(currentRepres->getAdress()->getFlatNumber()));
    ui->represInfoTelephone->setText(currentRepres->getConnections()->getTelephone());
    ui->represInfoEmail->setText(currentRepres->getConnections()->getEmail());

    ui->MainStackedWidget->setCurrentIndex(5);
}
void MainWindow::on_represInfoBackButton_2_clicked()
{
    ui->MainStackedWidget->setCurrentIndex(6);
}
void MainWindow::on_adminInfoButton_clicked()
{
    QString temp;

    ui->adminInfoSurname->setText(currentAdmin->getSurname());
    ui->adminInfoName->setText(currentAdmin->getName());
    ui->adminInfoSex->setText(currentAdmin->getSex()==M?"Male":"Female");
    ui->adminInfoOrganization->setText(currentAdmin->getOrganization());
    ui->adminInfoDob->setText(currentAdmin->getDob());
    ui->adminInfoCountry->setText(currentAdmin->getAdress()->getCountry());
    ui->adminInfoCity->setText(currentAdmin->getAdress()->getCity());
    ui->adminInfoStreet->setText(currentAdmin->getAdress()->getStreet());
    ui->adminInfoHouseNumber->setText(temp.setNum(currentAdmin->getAdress()->getHouseNumber()));
    ui->adminInfoFlatNumber->setText(temp.setNum(currentAdmin->getAdress()->getFlatNumber()));
    ui->adminInfoTelephone->setText(currentAdmin->getConnections()->getTelephone());
    ui->adminInfoEmail->setText(currentAdmin->getConnections()->getEmail());

    ui->MainStackedWidget->setCurrentIndex(10);
}
