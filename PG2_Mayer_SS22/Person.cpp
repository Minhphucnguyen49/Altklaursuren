#include "Person.h"



Person::Person(std::string p_name, int p_alter)
    :name{p_name}, age{p_alter}
{}

const std::string &Person::getId() const
{
    return id;
}

const std::string &Person::getName() const
{
    return name;
}

int Person::getAge() const
{
    return age;
}
