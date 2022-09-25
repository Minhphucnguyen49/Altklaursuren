#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "person.h"




class Employee : public Person
{
private:
    int category;
//    enum{Manager,Personaltrainer, Trainee} cate;
public:
    Employee(int&, string&, int&);
    string data() override;
    int salary();
    string getCategory();

    void setID_employee();
    Person* clone() const override;
    void setCategory(int newCategory);
    int getCategory_int() const;
};

#endif // EMPLOYEE_H
