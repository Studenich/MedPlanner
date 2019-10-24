#ifndef RESIDENCEADRESS_H
#define RESIDENCEADRESS_H
#include <QString>


class ResidenceAdress
{
public:
    ResidenceAdress();
    ResidenceAdress(QString newCountry,
                    QString newCity, QString newStreet,
                    int newHouseNumber, int newFlatNumber);

    void setCurrentAdress(QString newCountry,
                     QString newCity, QString newStreet,
                     int newHouseNumber, int newFlatNumber);

    QString getCountry();
    QString getCity();
    QString getStreet();
    int getHouseNumber();
    int getFlatNumber();

private:
    QString country;
    QString city;
    QString street;
    int houseNumber;
    int flatNumber;
};

#endif // RESIDENCEADRESS_H
