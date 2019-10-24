#include "employee.h"
#include "residenceadress.h"
#include "connections.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLineEdit>
#include <QDebug>


Employee::Employee()
{
    adress = new ResidenceAdress;
    connections = new Connections;
}

Employee::~Employee()
{
    delete adress;
    delete connections;
}

void Employee::setCurrent(QString currentLogin)
{
    QSqlQuery qry;

    if(QString::compare(currentLogin, "Admin", Qt::CaseInsensitive) == 0)
    {
        qry.exec("SELECT * FROM Admins");

        while (QString::compare(currentLogin, qry.value(0).toString(), Qt::CaseInsensitive) != 0)
        {
            qry.next();
        }

        login = qry.value(0).toString();
        password = qry.value(1).toString();;
        name = qry.value(2).toString();
        surname = qry.value(3).toString();
        organization = qry.value(4).toString();
        sex = Sex(qry.value(5).toInt());
        dob = qry.value(6).toString();

        adress->setCurrentAdress(qry.value(7).toString(),
                                 qry.value(8).toString(),
                                 qry.value(9).toString(),
                                 qry.value(10).toInt(),
                                 qry.value(11).toInt());
        connections->setCurrentConnections(qry.value(12).toString(),
                                           qry.value(13).toString());
    }
    else
    {
        qry.exec("SELECT * FROM Representatives");

        while (QString::compare(currentLogin, qry.value(0).toString(), Qt::CaseInsensitive) != 0)
        {
            qry.next();
        }

        login = qry.value(0).toString();
        password = qry.value(1).toString();;
        name = qry.value(2).toString();
        surname = qry.value(3).toString();
        organization = qry.value(4).toString();
        sex = Sex(qry.value(5).toInt());
        dob = qry.value(6).toString();

        adress->setCurrentAdress(qry.value(7).toString(),
                                 qry.value(8).toString(),
                                 qry.value(9).toString(),
                                 qry.value(10).toInt(),
                                 qry.value(11).toInt());
        connections->setCurrentConnections(qry.value(12).toString(),
                                           qry.value(13).toString());
    }
}

QString Employee::getLogin()
{
    return login;
}
QString Employee::getName()
{
    return name;
}
QString Employee::getSurname()
{
    return surname;
}
QString Employee::getOrganization()
{
    return organization;
}
Sex Employee::getSex()
{
    return sex;
}
QString Employee::getDob()
{
    return dob;
}
ResidenceAdress *Employee::getAdress()
{
    return adress;
}
Connections *Employee::getConnections()
{
    return connections;
}

