#include "person.h"

int Person::lastID = 1000000;

int Person::getAge() const
{
    return age;
}

const string &Person::getName() const
{
    return name;
}

unsigned int Person::getID() const
{
    return ID;
}

void Person::setID(unsigned int newID)
{
    ID = newID;
}

Person::Person(int &age, std::string &name)
    :age(age), name(name)
{}
