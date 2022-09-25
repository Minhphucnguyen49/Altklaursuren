#ifndef PERSON_H
#define PERSON_H

#include <iostream>
using namespace std;


class Person
{
protected:
    int age;
    string name;
    unsigned int ID;
    static int lastID;
public:
    Person(int& age, string& name);
    virtual ~Person() = default;
    virtual string data() = 0;
    int getAge() const;
    const string &getName() const;
    unsigned int getID() const;
    void setID(unsigned int newID);
    virtual Person* clone() const = 0;
};

#endif // PERSON_H
