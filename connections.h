#ifndef CONNECTIONS_H
#define CONNECTIONS_H
#include <QString>


class Connections
{
public:
    Connections();
    Connections(QString newEmail, QString newTelephone);

    void setCurrentConnections(QString newEmail, QString newTelephone);

    QString getEmail();
    QString getTelephone();

private:
    QString email;
    QString telephone;
};

#endif // CONNECTIONS_H
