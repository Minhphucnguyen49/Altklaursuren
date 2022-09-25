#include "fitnesscenter.h"

#include <iostream>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    FitnessCenter f;
//    f.terminalUI();
    f.readFile_JSON("Datenbank.json");

//    FitnessCenter fk = f;
////    f.deleteEmployee(0);
////    f.deleteEmployee(0);
////    f.deleteEmployee(0);

//    fk.addCustomer();
//    fk.addCustomer();
//    fk.printDatabase();

//    cout << "-------------------------------------------------------------" << endl;
//    f.printDatabase();
    FitnessCenter fz;
    fz.readFile_JSON("Datenbank.json");
    fz.deleteEmployee(53);
    cout << "fz's old Database" <<endl;
    fz.printDatabase();

    fz = f;

    cout << "fz's new Database" <<endl;
    fz.printDatabase();
    return 0;
}
