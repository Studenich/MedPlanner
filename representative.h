#ifndef REPRESENTATIVE_H
#define REPRESENTATIVE_H
#include <QString>
#include "employee.h"


class Representative : public Employee
{
public:
    Representative();

private:
    QString myAdmin = "admin";
};

#endif // REPRESENTATIVE_H
