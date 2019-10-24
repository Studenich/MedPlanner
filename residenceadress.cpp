#include "residenceadress.h"

ResidenceAdress::ResidenceAdress()
{

}

ResidenceAdress::ResidenceAdress(QString newCountry,
                                 QString newCity, QString newStreet,
                                 int newHouseNumber, int newFlatNumber)
{
    country = newCountry;
    city = newCity;
    street = newStreet;
    houseNumber = newHouseNumber;
    flatNumber = newFlatNumber;
}

void ResidenceAdress::setCurrentAdress(QString newCountry,
                 QString newCity, QString newStreet,
                 int newHouseNumber, int newFlatNumber)
{
    country = newCountry;
    city = newCity;
    street = newStreet;
    houseNumber = newHouseNumber;
    flatNumber = newFlatNumber;
}

QString ResidenceAdress::getCountry()
{
    return country;
}
QString ResidenceAdress::getCity()
{
    return city;
}
QString ResidenceAdress::getStreet()
{
    return street;
}
int ResidenceAdress::getHouseNumber()
{
    return houseNumber;
}
int ResidenceAdress::getFlatNumber()
{
    return flatNumber;
}
