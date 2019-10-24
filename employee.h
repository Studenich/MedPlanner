#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include "residenceadress.h"
#include "connections.h"

enum Sex
{
    M,
    F
};

class Employee
{
public:
    Employee();
    ~Employee();

    void setCurrent(QString currentLogin);

    QString getLogin();
    QString getName();
    QString getSurname();
    QString getOrganization();
    Sex getSex();
    QString getDob();
    ResidenceAdress *getAdress();
    Connections *getConnections();

private:
    QString login;
    QString password;

    QString name;
    QString surname;
    QString organization;
    Sex sex;
    QString dob;
    ResidenceAdress *adress;
    Connections *connections;
};

#endif // EMPLOYEE_H
