#ifndef OWNER_H
#define OWNER_H

#include <iostream>
using std::string;

class Owner
{
public:
    Owner(const string& name);
    const string &getName() const;
    void setName(const string &newName);

private:
    string name;
};

#endif // OWNER_H
