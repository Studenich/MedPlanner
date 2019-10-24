#ifndef NEWVISITWINDOW_H
#define NEWVISITWINDOW_H

#include <QDialog>

namespace Ui {
class NewVisitWindow;
}

class NewVisitWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewVisitWindow(QWidget *parent = 0);
    ~NewVisitWindow();

    void setCurrentLogin(QString newCurrentLogin);
    QString getCurrentLogin();

signals:
    void sendNewVisit(QString newOrganizationName,
                      QString newFullName,
                      QString newCurrentPosition,
                      QString newSpecialization,
                      QString newData);

private slots:
    void on_addVisitButton_clicked();
    void on_cancelVisitButton_clicked();

private:
    Ui::NewVisitWindow *ui;

    QString currentLogin;
};

#endif // NEWVISITWINDOW_H
