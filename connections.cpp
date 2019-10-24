#include "connections.h"

Connections::Connections()
{

}

Connections::Connections(QString newEmail, QString newTelephone)
{
    email = newEmail;
    telephone = newTelephone;
}

void Connections::setCurrentConnections(QString newEmail, QString newTelephone)
{
    email = newEmail;
    telephone = newTelephone;
}

QString Connections::getEmail()
{
    return email;
}
QString Connections::getTelephone()
{
    return telephone;
}
