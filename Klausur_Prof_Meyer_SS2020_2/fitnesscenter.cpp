#include "customer.h"
#include "fitnesscenter.h"

#include <json.hpp>
#include "fstream"
#include "sstream"

using namespace nlohmann;

FitnessCenter::FitnessCenter()
{
//    int i = 25;
//    string name = "Phuc";
//    addCustomer(i, name);
//    i = 56;
//    name = "Than";
//    addCustomer(i, name);
//    i = 65;
//    name = "Trrung";
//    addCustomer(i, name);
//    i += 5;
//    int cate = 2;
//    name+="Jamil";
//    addEmployee(i, name ,cate);
//    i = 27;
//    cate = 1;
//    name = "Caleb";
//    addEmployee(i, name ,cate);
//    i = 34;
//    cate = 3;
//    name = "Simon";
//    addEmployee(i, name ,cate);

}

FitnessCenter::~FitnessCenter()
{
    std::map<int, Person*>::iterator it = personMap.begin();
    int count = 0;
    for (; it != personMap.end(); it++)
    {
        delete it->second;
        personMap.erase(it);
        count++;
//        cout << "Destruktor written correctly " << count << " times" << endl;
    }
    cout << count << endl;
//    printDatabase();
//    for (auto& pm : personMap)
//    {
//        cout << "Destructor has " << personMap.size() - count << " elements left!" << endl;
    //    }
}

FitnessCenter::FitnessCenter(const FitnessCenter &other)
{
    for(auto& m : other.personMap)
    {
        Person* p = m.second->clone();
        personMap[m.first] = p;
    }

    //not sure if I need the clone() stuff??? After several experiments, there's no distinguised differences between with and without clone()
    for(auto& m : other.personMap)
    {
        Employee* e = dynamic_cast<Employee*>(m.second);
        if (e != nullptr)
        {
            int age = e->getAge();
            unsigned int ID = e->getID();
            string name = e->getName();
            int category = e->getCategory_int();
            personMap.insert({ID, new Employee(age, name, category)});
        }
        else {
            Customer* c = dynamic_cast<Customer*>(m.second);
            int age = c->getAge();
            unsigned int ID = c->getID();
            string name = c->getName();
            personMap[ID] = new Customer(age, name);
            if(c->getPEmp() != nullptr){
                dynamic_cast<Customer*>(personMap[c->getID()])->setPEmp(c->getPEmp());//why???
            }
        }
    }
}

void FitnessCenter::printDatabase()
{
    std::map<int, Person*>::iterator it = personMap.begin();
    for (; it != personMap.end(); it++)
    {
//        if (typeid(*it).name() == typeid(Customer).name())
//        {

//        }
//        cout << (*it->second).data();
        cout << (it->second)->data();
    }
    cout << "Map's size = " << personMap.size() << endl;
}

void FitnessCenter::addEmployee(int &age_, string &name_, int &category_)
{

    Employee* e = new Employee(age_, name_, category_);
    unsigned int ID_;
    cout << "Enter ID: ";
    if (cin>>ID_)
    {
        e->setID(ID_);
    }
    else
    {
        e->setID_employee();
    }
    personMap.insert(make_pair(e->getID(),e));
}

void FitnessCenter::addCustomer(int &age_, string &name_)
{
    Customer* c = new Customer(age_, name_);
    unsigned int ID_;
    cout << "Enter ID: ";
    if (cin>>ID_)
    {
        c->setID(ID_);
    }
    else
    {
        c->setID_customer();
    }
    personMap.insert({c->getID(),c});
}

void FitnessCenter::addTrainer(unsigned int customerID, unsigned int employeeID)
{

    std::map<int, Person*>::iterator it = personMap.begin();

    for (; it != personMap.end(); it++)
    {
        if (typeid(*(it->second)).name() == typeid(Customer).name())
        {
            Customer* c = dynamic_cast<Customer*>(it->second);
            if (c->getID() == customerID)
            {
                std::map<int, Person*>::iterator it2 = personMap.begin();
                for (; it2 != personMap.end(); it2++)
                {
                    if (typeid(*(it2->second)).name() == typeid(Employee).name())
                    {
                        Employee* e = dynamic_cast<Employee*>(it2->second);
                        if (e->getID() == employeeID)
                        {
                            c->pEmp = e;
                        }
                    }
                }

            }

        }
    }
}
void FitnessCenter::addTrainer_Umar(int customerID, int employeeID)
{
    auto searchID = personMap.count(customerID);
    if (searchID == 0){
        cout << "ID existiert nicht" << endl;
        return;
    }

    searchID = personMap.count(employeeID);
    if (searchID == 0){
        cout << "ID existiert nicht" << endl;
        return;
    }

    auto searchEmployeeID = personMap.find(employeeID);
    if (searchEmployeeID != personMap.end()){
        Employee* e = dynamic_cast<Employee*>(searchEmployeeID->second);
        if(e==nullptr){
            cout << "Ubergebene ID des Mitarbeiter gehoert keinem Mitarbeiter" << endl;
            return;
        }

        else {
            auto searchCustomerID = personMap.find(customerID);
            if (searchCustomerID != personMap.end()){
                Customer* c = dynamic_cast<Customer*>(searchCustomerID->second);
                if(c==nullptr){
                    cout << "Ubergebene ID des Kunden gehoert keinem Kunden" << endl;
                    return;
                }
                else {
                    c->setPEmp(e);
                }
            }
        }
    }


}

void FitnessCenter::readFile_JSON(const string &path)
{
//    ifstream file("../" + path);
    ifstream file(path);

    if (!file.good())
    {
        throw runtime_error("JSON File can not be opened!");
    }
//    string line; file >> line;
//    int numberofCustomer; file >> numberofCustomer;
//    file >> line;
//    int numberofEmployee; file >> numberofEmployee;

    json j;
    file >> j; //komplette JSON Datei in Stream laden;
    for (auto& e : j["Mitarbeiter"])
    {
        int age = e["Alter"];
        unsigned int ID = e["ID"];
        string name = e["Name"];
        string cate = e["Gehaltsklasse"];

        if (cate == "Manager")
        {
            int manager = 1;
            personMap[ID] = new Employee(age,name,manager);
        }
        if (cate == "Trainer")
        {
            int manager = 2;
            personMap[ID] = new Employee(age,name,manager);
        }
        if (cate == "Trainee")
        {
            int manager = 3;
            personMap[ID] = new Employee(age,name,manager);
        }

    }

    for (auto& c : j["Kunden"])// Kunden Array durchiterieren
    {
        int age = c["Alter"];
        unsigned int ID = c["ID"];
        string name = c["Name"];
        int trainerID;
        if ( c.contains("TrainerID") ){
            trainerID = c["TrainerID"];
            Employee* e = dynamic_cast<Employee*>(personMap[trainerID]);
            //save Employee in map first (durch iterieren j["Mitarbeiter"] first)
            //so that personMap[trainerID] is not meaningless
            personMap[ID] = new Customer(age,name,ID,e);
        }else {
            personMap[ID] = new Customer(age,name,ID,nullptr);
        }
    }

}

void FitnessCenter::readFile_CSV(const string &path)
{
    ifstream file(path);

    if (!file.good())
    {
        throw runtime_error("CSV File can not be opened!");
    }

    std::string line;
    file >> line; file >> line;
    int numberofEmployee; file >> numberofEmployee;

    getline(file, line);//read and discard the line "Name;Alter;ID;Gehaltsklasse"

    for (int i = 0;  i < numberofEmployee; i++)
    {
        getline(file, line, '\n');

        std::stringstream tmp(line);
        std::string col;

        getline (tmp, col, ';'); std::string name_ = col;
        getline (tmp, col, ';'); int age_ = std::stoi(col);
        getline (tmp, col, ';');  int id_ = std::stoi(col);
        getline (tmp, col, ';'); int category_ = std::stoi(col);
        personMap.insert( {id_, new Employee(age_, name_, category_)} );
    }

    file >> line; file >> line;
    int numberofCustomer; file >> numberofCustomer;
    getline(file, line);//read and discard the line "Name;Alter;ID;TrainerID"
    for (int i = 0;  i < numberofCustomer; i++)
    {
        getline(file, line, '\n');

        std::stringstream tmp(line);
        std::string col;
        getline (tmp, col, ';'); std::string name_ = col;
        getline (tmp, col, ';'); int age_ = std::stoi(col);
        getline (tmp, col, ';'); unsigned int id_ = std::stoi(col);
        getline (tmp, col, ';'); int trainerID_ = std::stoi(col);
        Employee* e = dynamic_cast<Employee*>(personMap[trainerID_]);
        personMap.insert( {id_, new Customer(age_, name_,id_, e)} );
    }

}


int FitnessCenter::income()
{
    int income = 0;
    std::map<int, Person*>::iterator it = personMap.begin();

    for (; it != personMap.end(); it++)
    {
        if (typeid(*(it->second)).name() == typeid(Customer).name())
        {
            Customer* c = dynamic_cast<Customer*>(it->second);
            income += c->membershipFee();
        }
        if (typeid(*(it->second)).name() == typeid(Employee).name())
        {
            Employee* e = dynamic_cast<Employee*>(it->second);
            income -= e->salary();
        }
    }
    return income;
}

void FitnessCenter::deleteEmployee(int ID)
{
    auto employee = personMap.find(ID);
    if (employee != personMap.end())
    {
        delete employee->second;
        personMap.erase(employee);
    }
}

void FitnessCenter::addTrainer()
{
    unsigned customerID, employeeID;
    cout << "Enter customer ID: "; cin >> customerID;
    cout << "Enter employee ID: "; cin >> employeeID;
//    addTrainer(customerID, employeeID);
    addTrainer_Umar(customerID, employeeID);
}

void FitnessCenter::addEmployee()
{
    int age_; string name_; int category_;
    cout << "Enter age: "; cin >> age_;
    cout << "Enter name: "; cin >> name_;
    cout << "Enter category(1-Ma/2-Trainer/3-Trainee): "; cin >> category_;
    addEmployee(age_, name_,category_);
}

void FitnessCenter::addCustomer()
{
    int age_; string name_;
    cout << "Enter age: "; cin >> age_;
    cout << "Enter name: "; cin >> name_;
    addCustomer(age_, name_);
}

void FitnessCenter::terminalUI()
{
    string rt = "";
    rt += "Bitte treffen Sie ihre Wahl:\n";
    rt += "p/P: Liste aller Personen\n";
    rt += "c/C: Customer hinzufuegen\n";
    rt += "e/E: Employee hinzufuegen\n";
    rt += "a/A: Trainer hinzufuegen\n";
    rt += "i/I: Einkommen/Bilanz des Centers berechnen\n";
    rt += "d/D: Mitarbeiter loeschen\n";
    rt += "r: JSON file lesen\n";
    rt += "x/X: Vorgang abbrechen\n";

//    int age_; string name_; int category_;
//    unsigned customerID, employeeID;

    char button = ' ';

    do
    {
        cout << rt;
        cin >> button;
        cin.clear();cin.get();
        switch(button)
        {
        case 'P':
        case 'p': printDatabase(); break;
        case 'C':
        case 'c': {
            addCustomer();
            break;
        }
        case 'E':
        case 'e': {
            addEmployee();
            break;
        }
        case 'A':
        case 'a':{
            addTrainer();
            break;
        }
        case 'I':
        case 'i': cout << "Income: " + to_string(income()); break;
        case 'D':
        case 'd':{
            int id_;
            cout << "Enter Id: "; cin >> id_;
            deleteEmployee(id_);
            break;
        }
        case 'r': readFile_JSON("Datenbank.json");break;
        case 'R': readFile_CSV("Datenbank.csv");break;
        case 'x':
        case 'X': return;
        default: break;
        }
    }
    while (true);
}

void swapMap(FitnessCenter& lhs, FitnessCenter& rhs){ //Aufgabe 3 Zuweisungsoperator Hilfsfunktion

    std::swap(lhs.personMap,rhs.personMap);
}


FitnessCenter& FitnessCenter::operator=(FitnessCenter rhs){ //Aufgabe 3 - Zuweisungsoperator
    swapMap(*this, rhs);
    return *this;
}
//bool FitnessCenter::operator=(const FitnessCenter& rhs) const
//{
//    for (auto& m1 : personMap)
//    {
//        if (m1.first == rhs.)
//    }
//}
