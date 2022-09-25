#include "customer.h"
using std::to_string;


Customer::Customer(int &age, std::string &name)
    : Person(age, name)
{
    pEmp = nullptr;
}

Customer::Customer(int &age, string &name, unsigned int &ID_, Employee *pEmp_)
    :Person(age, name)
{
    ID = ID_;
    pEmp = pEmp_;
}

string Customer::data()
{
    string ret = "";
    ret += " Name " + name;
    ret += " Age " + to_string(age);
    ret += " Fee: " + to_string(membershipFee());
    ret += " ID: " + to_string(getID());
    if (pEmp)// pEmp != nullptr
    {
        ret += " Personal Trainer: " + pEmp->getName();
    }else ret += " Personal Trainer: still not assigned!";
    ret += "\n";
    return ret;
}

int Customer::membershipFee()
{
    if (age > 65)
        return 40;
    if (age < 18)
        return 40;
    return 60;
}

Employee *Customer::getPEmp() const
{
    return pEmp;
}

void Customer::setPEmp(Employee *newPEmp)
{
    pEmp = newPEmp;
}

Person *Customer::clone() const
{
    return new Customer(*this);
}

void Customer::setID_customer()
{
    ID = ++lastID + 1000000;
}
