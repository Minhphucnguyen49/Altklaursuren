#ifndef FITNESSCENTER_H
#define FITNESSCENTER_H
#include "Person.h"
#include <list>
#include "Customer.h"
#include "Employee.h"

class FitnessCenter
{
public:
    /**
     * @brief FitnessCenter this Constructor works as a Level constructor in Prak:
     * IN this class, there will be all objects angelegt
     *
     * Terminal User Interface should also be put here
     * (instead of making another class like Dungeon Crawler
     */
    FitnessCenter();
    ~FitnessCenter();
    void terminalUI();
    void printDatabase() const;
    void addCustomer(Customer* pCustomer);
    void addEmployee(Employee* pEmployee);
    void addCustomer();
    void addEmployee();
    int income() const;
    std::list<Person*>::iterator  find(std::string ID);
    void deleteCustomer(std::string ID);
    void sortDatabase();
    void saveFile_JSON(const std::string& path);
    void saveFile_CSV (const std::string& path);
private:
    std::list<Person*> interessantePersonen;
};

#endif // FITNESSCENTER_H
