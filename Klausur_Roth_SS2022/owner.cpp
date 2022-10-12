#include "owner.h"

Owner::Owner(const std::string &name_in)
    :name (name_in)
{

}

const string &Owner::getName() const
{
    return name;
}

void Owner::setName(const string &newName)
{
    name = newName;
}
