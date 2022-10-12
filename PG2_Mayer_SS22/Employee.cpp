#include "Employee.h"

static int e_counter = 0;

Employee::Employee(std::string p_name, int p_alter, int p_category)
    :Person(p_name, p_alter), category{p_category}
{ 
    e_counter++;
    id = "E" + std::to_string(e_counter);
}

std::string Employee::data()
{
    std::string type = "Trainee ";
    if ( category == 1)
        type = "Manager ";
    if ( category == 2)
        type = "Personal Trainer ";

    std::string data = type + name + "\t is\t" + std::to_string(age) + " years old.\t"
            + "ID " + id
                         + " Salary: " + std::to_string(salary());
    return data;
}

int Employee::salary()
{
    if (category == 1)
        return 1500;
    if (category == 2)
        return 1000;
    return 450;
}

std::string Employee::getId() const
{
    return id;

}

std::string Employee::getCategory() const
{
    switch(category)
    {
    case 1: return "Manager";
    case 2: return "Trainer";
    case 3: return "Trainee";
    }
    return "";
}


