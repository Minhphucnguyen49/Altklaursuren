#ifndef PERSON_H
#define PERSON_H

#include <iostream>
//using namespace std;//kein Punktabzug darf man nur in C++

class Person
{
protected:
    std::string name;
    int age;
    std::string id;
public:
    Person(std::string p_name, int p_alter);
    virtual ~Person() = default;//wichtig
    virtual std::string data() = 0;
    const std::string &getId() const;
    const std::string &getName() const;
    int getAge() const;
};

#endif // PERSON_H
