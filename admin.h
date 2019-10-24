#ifndef ADMIN_H
#define ADMIN_H
#include "representative.h"
#include "employee.h"


class Admin : public Employee
{
public:
    Admin();
    ~Admin();

private:
    Representative *representatives;
};

#endif // ADMIN_H
