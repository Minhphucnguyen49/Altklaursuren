#include "Fitnesscenter.h"
#include "names.h"
#include <algorithm>// für find()
#include <json.hpp>
#include <random>
#include "json.hpp"
#include <fstream>
using namespace nlohmann;

FitnessCenter::FitnessCenter()
{
    /**
     * @caution:(highly important)
     * Objekt auf Heap erstellen und dann in List pushen hat geklappt
     * auf Stack zu erstellen hat nicht funktioniert.
     */
    //int age = std::rand()%50; and in main() use srand(time(nullptr)); as a seed
    //include <ctime>

    std::random_device r;
    std::default_random_engine e1(r());
    //---
    std::uniform_int_distribution<int> uniform_dist(0, 49);

    int randomNameIndex = uniform_dist(e1);
    std::string emp_name = first_name_female[randomNameIndex] + " " + last_name[randomNameIndex];

    std::uniform_int_distribution<int> uniform_dist_age(20, 80);
    int age = 0;
    age = uniform_dist_age(e1);
    Employee* E1 = new Employee(emp_name, age, 1);
    interessantePersonen.push_back(E1);

    randomNameIndex = uniform_dist(e1);
    emp_name = first_name_female[randomNameIndex] + " " + last_name[randomNameIndex];
    age = uniform_dist_age(e1);
    E1 = new Employee(emp_name, age, 2);
    interessantePersonen.push_back(E1);

    randomNameIndex = uniform_dist(e1);
    emp_name = first_name_female[randomNameIndex] + " " + last_name[randomNameIndex];
    age = uniform_dist_age(e1);
    E1 = new Employee(emp_name, age, 2);
    interessantePersonen.push_back(E1);

    randomNameIndex = uniform_dist(e1);
    emp_name = first_name_female[randomNameIndex] + " " + last_name[randomNameIndex];
    age = uniform_dist_age(e1);
    E1 = new Employee(emp_name, age, 3);
    interessantePersonen.push_back(E1);

    randomNameIndex = uniform_dist(e1);
    emp_name = first_name_female[randomNameIndex] + " " + last_name[randomNameIndex];
    age = uniform_dist_age(e1);
    E1 = new Employee(emp_name, age, 3);
    interessantePersonen.push_back(E1);

    //----------------------------------
    std::string name;
    for (int i = 0; i < 50; i++)
    {
        age = uniform_dist_age(e1);
        name = first_name_male[i] + " " + last_name[i];
        Customer* C = new Customer(name, age);
        interessantePersonen.push_back(C);
    }
    for (int i = 0; i < 50; i++)
    {
        age = uniform_dist_age(e1);
        name = first_name_female[i] + " " + last_name[i];
        Customer* C = new Customer(name, age);
        interessantePersonen.push_back(C);
    }
}

FitnessCenter::~FitnessCenter()
{
    /** How to write Destructor:
     *  durch iterieren + delete each elements
     *  Problem war: in Person class there was no virtual destructor.
     *  --> add virtual destructor
     *
     */
    for(Person* iP : interessantePersonen)
    {
        delete iP;
    }

}

int FitnessCenter::income() const
{
    double income = 0.0;
    for (Person* interest_Person : interessantePersonen)
    {
        if (typeid(*interest_Person) == typeid(Customer))
        {
            income += dynamic_cast<Customer*>(interest_Person)->CustomerFee();
        }
        if (typeid(*interest_Person) == typeid(Employee))
        {
            income -= dynamic_cast<Employee*>(interest_Person)->salary();
        }
    }
    return income;
}


std::list<Person*>::iterator FitnessCenter::find(std::string ID)
{
    std::list<Person*>::iterator it = interessantePersonen.begin();
    std::list<Person*>::iterator id_iterator;
    for (; it != interessantePersonen.end(); it++)
    {
        if ((*it)->getId() == ID)
        {
            return it;
            id_iterator = it;
            std::cout << "Person with ID " + ID + " is deleted successfully!" << std::endl;
            //alternativ kann man break; benutzen
            //und "it" direkt daunten return anstatt id_iterator
        }
    }
    if(it == interessantePersonen.end()) throw("Id" + ID + " not found!");
    return id_iterator;
}

void FitnessCenter::deleteCustomer(std::string ID)
{
    //Key point here is: find(ID) will return an iterator
    if(find(ID) != interessantePersonen.end())//if ID found
    {
       //we don't need to do this if condition because if ID not found,
       //the programm will be stopped
       //thanks to the exeption handling in find methode
    }
    std::list<Person*>::iterator it_id = find(ID);
    delete *it_id;
    //super important - avoid memory leaks:
    //delete the pointer of iterator(dereference) before erase iterator
    interessantePersonen.erase(it_id);
}

void FitnessCenter::sortDatabase()
{
    std::vector<Person*> personlist;
    for(Person* a : interessantePersonen)
    {
        //Vector immer push_back()
        personlist.push_back(a);
    }
    std::sort(personlist.begin(), personlist.end(),
              [](const Person* lhs, const Person* rhs)
                { return lhs->getAge() < rhs->getAge();}
              );

    interessantePersonen.clear();//list::clear() clear the whole list
    for(Person* a : personlist)
    {
        interessantePersonen.push_back(a);
    }
}

void FitnessCenter::saveFile_JSON(const std::string& path)
{
    nlohmann::json j;
    int numberofEmployee = 0;
    for(Person* p : interessantePersonen)
    {
        if(typeid(*p).name() == typeid(Employee).name())
        {
            numberofEmployee ++;
        }
    }
    int numberofCustomer = interessantePersonen.size() - numberofEmployee;
    j["Number of Customers"] = numberofCustomer;
    j["Number of Employees"] = numberofEmployee;

    for(Person* p : interessantePersonen)
    {
        json customer;
        if(typeid(*p).name() == typeid(Customer).name())
        {
            customer["Age"] = p->getAge();
            customer["ID"] = p->getId();
            customer["Name"] = p->getName();
            j["Customer"].push_back(customer);
        }
        json employee;
        if(typeid(*p).name() == typeid(Employee).name())
        {
            Employee* e = dynamic_cast<Employee*>(p);
            employee["Age"] = p->getAge();
            employee["salary's category"] = e->getCategory();
            employee["ID"] = p->getId();
            employee["Name"] = p->getName();
            j["Employee"].push_back(employee);
        }
    }
    std::ofstream file(path);
    if ( !file.good() )
    {
        throw ("file can not be opened");
    }
    file << std::setw(4) << j << std::endl;
}

void FitnessCenter::saveFile_CSV(const std::string &path)
{
    std::ofstream file(path);
    int numberofEmployee = 0;
    for(Person* p : interessantePersonen)
    {
        if(typeid(*p).name() == typeid(Employee).name())
        {
            numberofEmployee ++;
        }
    }
    file << "Anzahl Mitarbeiter: " << numberofEmployee << std::endl;
    file << "Name;Alter;ID;Gehaltsklasse"<< std::endl;
    for(Person* p : interessantePersonen)
    {
        if(typeid(*p).name() == typeid(Employee).name())
        {

            file << p->getName() << ";";
            file << p->getAge() << ";";
            file << p->getId() << ";";
            file << dynamic_cast<Employee*>(p)->getCategory() << ";";
            file << std::endl;
        }
    }
    file << "Anzahl Kunden: " << interessantePersonen.size() - numberofEmployee << std::endl;
    file << "Name;Alter;ID" << std::endl;
    for(Person* p : interessantePersonen)
    {
        if(typeid(*p).name() == typeid(Customer).name())
        {
            file << p->getName() << ";";
            file << p->getAge() << ";";
            file << p->getId() << ";";
            file << std::endl;
        }
    }
    if ( !file.good() )
    {
        throw ("file can not be opened");
    }
}

void FitnessCenter::printDatabase() const
{
    for(Person* iP : interessantePersonen)
    {
        std::cout << "";
        if ( iP->getId().substr(0, 1) == "E" )//alternativ (Simons Ansatz): typeid(*iP) == typeid(Customer)
        {
            std::cout << dynamic_cast<Employee*>(iP)->data() << std::endl;

        }
        if ( iP->getId().substr(0, 1) == "C")
        {
            std::cout << dynamic_cast<Customer*>(iP)->data() << std::endl;
        }
    }
}

void FitnessCenter::addCustomer(Customer *pCustomer)
{
    //Ein anderer Ansatz von Prof.Meyer: using for loop + if statement comparing id
    for(auto& p : interessantePersonen)
    {
        if( p->getId() == pCustomer->getId() )
            throw std::runtime_error("This Customer is already in the list!");
    }
     /* personList.push_back(pCustomer);
     */
//    if (std::find(interessantePersonen.begin(), interessantePersonen.end(), pCustomer) != interessantePersonen.end())
//    {
//        throw ("This Customer is already in the list!");
//    }
    interessantePersonen.push_back(pCustomer);
}

void FitnessCenter::addEmployee(Employee *pEmployee)
{
    if (std::find(interessantePersonen.begin(), interessantePersonen.end(), pEmployee) != interessantePersonen.end())
    {
        throw ("This Employee is already in the list!");
    }
    if (income() <= 0)
    {
        throw ("Recruiting this Employee creates negative income");
    }
    interessantePersonen.push_back(pEmployee);
}

void FitnessCenter::addCustomer()
{
    std::cout << " Please enter the following information: " << std::endl;
    std::cout << " Customer's Name: ";
    std::string name; getline(std::cin, name);
    std::cout << " Customer's age: ";
    int age; std::cin >> age;
    Customer* customer = new Customer(name, age);
    addCustomer(customer);
}

void FitnessCenter::addEmployee()
{
    std::cout << " Please enter the following information: " << std::endl;
    std::cout << " Employee's Name: ";
    std::string name; getline(std::cin, name);
    std::cout << " Employee's age: ";
    int age; std::cin >> age;
    std::cout << " Employee's category: ";
    int category; std::cin >> category;
    Employee* E = new Employee(name, age, category);
    addEmployee(E);
}

void FitnessCenter::terminalUI()
{
    char button = ' ';
    std::string id_in;
    do {
        std::cout << "-----------MENU-----------" << std::endl;
        std::cout << "Enter <p/P> to print out database" << std::endl;
        std::cout << "Enter <i/I> for income" << std::endl;
        std::cout << "Enter <c/C> to add Customer" << std::endl;
        std::cout << "Enter <e/E> to add Employee" << std::endl;
        std::cout << "Enter <f> to find Employee/ Customer with given ID" << std::endl;
        std::cout << "Enter <d> to delete Employee/ Customer with given ID" << std::endl;
        std::cout << "Enter <s> to sort database" << std::endl;
        std::cout << "Enter <j> to save file in JSON form" << std::endl;
        std::cout << "Enter <v> to save file in JSON form" << std::endl;
        std::cout << "Enter <x/X> to exit" << std::endl;
        std::cout << "Please : "; std::cin >> button;
        std::cin.clear();
        std::cin.get();

        switch(button)
        {
        case 'p':
        case 'P': printDatabase(); break;
        case 'i':
        case 'I': std::cout << "FitnessCenter's income is "
                            << income() << " Euro." << std::endl; break;
        case 'c':
        case 'C': try {
                addCustomer();
            }
            catch ( std::runtime_error& e )
            {
                std::cerr << e.what() << std::endl;
            }
            break;
        case 'e':
        case 'E': addEmployee(); break;

        case 'f': std::cout << "Enter id "; std::cin >> id_in; find(id_in); break;
        case 'd': std::cout << "Enter id "; std::cin >> id_in; deleteCustomer(id_in); break;
        case 's': sortDatabase();break;
        case 'j': saveFile_JSON("listJSON.txt"); break;
        case 'v': saveFile_CSV("listCSV.txt"); break;
        case 'x':
        case 'X': break;
        default: break;
        }
    } while ( button != 'x' && button != 'X');
}
//    j["Customer"] = json::array();
//    j["Customer"]["ID"] = json::array();
//    j["Customer"]["Name"] = json::array();
//    j["Employee"] = json::array();
//    j["Employee"]["Age"] = json::array();
//    j["Employee"]["salary's category"] = json::array();
//    j["Employee"]["ID"] = json::array();
//    j["Employee"]["Name"] = json::array();

//    for (auto it = j.begin(); it != j.end(); it++)
//    {

//    }
