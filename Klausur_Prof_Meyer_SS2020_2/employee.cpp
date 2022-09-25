#include "employee.h"


int Employee::getCategory_int() const
{
    return category;
}

Employee::Employee(int& age, std::string& name, int& category_)
    :Person(age, name), category(category_)
{}

string Employee::data()
{
    string ret = "";
    ret += " Name " + name;
    ret += " Age " + to_string(age);
    ret += " Category " + getCategory();
    ret += " ID: " + to_string(getID());
    ret += "\n";
    return ret;
}

int Employee::salary()
{
    if (category == 1)
    {
        return 1500;
    }
    if (category == 2)
    {
        return 1000;
    }
    return 450;
}

string Employee::getCategory()
{
    switch(category)
    {
    case 1: return "Manager";
    case 2: return "Personal Trainer";
    default: return "Trainee";
    }
}


void Employee::setID_employee()
{
    //eindeutig ID
    ID = ++lastID;
}

Person *Employee::clone() const
{
    return new Employee(*this);
}

