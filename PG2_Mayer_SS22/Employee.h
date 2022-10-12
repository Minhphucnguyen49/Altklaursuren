#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"
class Employee : public Person
{
private:
    int category;

public:
    Employee(std::string p_name, int p_alter, int category);
    std::string data() override;
    /**
     * @brief salary
     * @return Gehalt des Mitarbeiters:
     * Manager -> 1500
     * Personal Trainer -> 1000
     * Trainee -> 450
     */
    int salary();
    std::string getId() const;
    std::string getCategory() const;
};

#endif // EMPLOYEE_H



