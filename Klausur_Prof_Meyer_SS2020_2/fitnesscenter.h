#ifndef FITNESSCENTER_H
#define FITNESSCENTER_H

#include "person.h"

#include <map>


class FitnessCenter
{
private:
    std::map<int, Person*> personMap;
public:
    FitnessCenter();
    ~FitnessCenter();

    FitnessCenter(const FitnessCenter& f);
    void printDatabase();
    void addEmployee(int&age_, string&name_,int&category_);
    void addCustomer(int&age_, string&name_);
    void addTrainer(unsigned int customerID, unsigned int employeeID);
    int income();
    void deleteEmployee(int ID);
    void terminalUI();
    void addTrainer();
    void addEmployee();
    void addCustomer();
    void addTrainer_Umar(int customerID, int employeeID);
    void readFile_JSON(const string& path);
    void readFile_CSV(const string& path);
    //this time key is integer --> no need for operator <

    /*
    Erweitern Sie die FitnessCenter-Klasse außerdem um einen uberladenen Vergleichsoperator. Zwei Fit- ¨
    nessCenter gelten als gleich, wenn exakt die gleichen Personen in der gleichen Reihenfolge in den beiden
    Maps gespeichert sind.
    */
    /*--Vergleichspoperator--*/
    bool operator=(const FitnessCenter& rhs) const;// no so hard but I have to ask Simon


    friend void swapMap(FitnessCenter& lhs, FitnessCenter& rhs);
    FitnessCenter &operator =(FitnessCenter rhs);
};

#endif // FITNESSCENTER_H
