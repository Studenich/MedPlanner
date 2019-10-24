#include "newvisitwindow.h"
#include "ui_newvisitwindow.h"

NewVisitWindow::NewVisitWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewVisitWindow)
{
    ui->setupUi(this);
}

NewVisitWindow::~NewVisitWindow()
{
    delete ui;
}

void NewVisitWindow::setCurrentLogin(QString newCurrentLogin)
{
    currentLogin = newCurrentLogin;
}
QString NewVisitWindow::getCurrentLogin()
{
    return currentLogin;
}

void NewVisitWindow::on_addVisitButton_clicked()
{
    emit sendNewVisit(ui->organizationLineEdit->text(),
                      ui->fullNameLineEdit->text(),
                      ui->currentPositionLineEdit->text(),
                      ui->specializationLineEdit->text(),
                      ui->dataLineEdit->text());

    QWidget::close();
}
void NewVisitWindow::on_cancelVisitButton_clicked()
{
    QWidget::close();
}
