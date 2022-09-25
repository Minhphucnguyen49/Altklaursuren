#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "employee.h"
#include "person.h"



class Customer : public Person
{
public:
    Customer(int&, string&);
    Customer(int&age, string&name, unsigned int& ID, Employee* pEmp);
    string data() override;
    int membershipFee();
    Employee* pEmp;
    void setID_customer();
    void setPEmp(Employee *newPEmp);
    Person* clone() const override;
    Employee *getPEmp() const;
};

#endif // CUSTOMER_H
