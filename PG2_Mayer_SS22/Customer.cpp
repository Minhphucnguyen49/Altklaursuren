#include "Customer.h"

/**
 * @brief c_counter
 * when this variable is defined without static (int c_counter = 0) - aka global variable
 * it will hold its scope for the whole programm??
 * and it will create excecute problem in Employee.cpp
 * (in which the same c_counter is used)
 *
 * By using static, on the other hand, it would be signified
 * as a global variable only within its class - Customer.cpp
 */

static int counter = 0;

Customer::Customer(std::string p_name, int p_alter)
    :Person(p_name, p_alter)
{
    counter++;
    id = "C" + std::to_string(counter);
}

std::string Customer::data()
{
    std::string s = "Customer " + name + "\t is\t" + std::to_string(age) + " years old.\t"
                  + "ID " + id
                  + " Customer Fee: " + std::to_string(CustomerFee());
    return s;
}

std::string Customer::getId() const
{
    return id;
}

int Customer::CustomerFee()
{
    if (age > 60 || age < 25)
    {
        return 40;
    }
    return 60;
}
