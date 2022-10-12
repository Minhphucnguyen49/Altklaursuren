#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"

class Customer : public Person
{
public:
    Customer(std::string p_name, int p_alter);
    std::string data() override;
    std::string getId() const;

    /**
     * @brief CustomerFee
     * @return Mitgliedsbeitrag des Kunden zurückgeben
     * Kunden < 25 || Kunden > 60 --> 40 Euro
     * Sonst --> 60 Euro
     */
    int CustomerFee();
};

#endif // CUSTOMER_H
