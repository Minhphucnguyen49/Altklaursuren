#include "farmingsimulator.h"
#include "pasture.h"

FarmingSimulator::FarmingSimulator(int rows, int columns)
{
    plotList.resize(rows);
    for( int x = 0; x < rows; x++)
    {
        for ( int y = 0; y < columns; y++)
        {
            plotList.at(x).push_back(nullptr);
        }
    }
//    Orchard* o1 = new Orchard(1,2,new Owner("MP"),10);
//    Orchard* o2 = new Orchard(0,1,new Owner("JB"));
//    Orchard* o3 = new Orchard(0,2,new Owner("FN"));
//    Orchard* o4 = new Orchard(0,3,new Owner("DM"));

//    Pasture* o5 = new Pasture(0,0,new Owner("MP"),10);
//    Pasture* o6 = new Pasture(0,1,new Owner("JB"));
//    Pasture* o7 = new Pasture(0,0,new Owner("FN"));
//    Pasture* o8 = new Pasture(0,1,new Owner("SK"));

//    addPlot(1,2,"MP", o1);
//    addPlot(1,2,"MP", o5);
//    addPlot(1,2,"MP", o3);
//    addPlot(1,2,"MP", o4);
//    addPlot(1,2,"MP", o5);
//    addPlot(1,2,"MP", o6);
//    addPlot(1,2,"MP", o7);
//    addPlot(1,2,"MP", o8);
}
/*
* Der Name eines Besitzers muss eindeutig sein.
* Konnte ein neuer Besitzer angelegt werden, so gibt die Methode true zurück.
* War der übergebene Name bereits vorhanden, wird kein neuer Besitzer erzeugt und die
Methode liefert false zurück.

    The above-mentioned criteria are also characteristics of a set (siehe Notion)
*/
bool FarmingSimulator::createOwner(const std::string &name)
{
    std::pair<std::set<Owner*>::iterator, bool> status = ownerList.insert(new Owner(name));
    return status.second;
}

Owner *FarmingSimulator::getOwner(const std::string &name)
{
    Owner* ow = new Owner(name);
    //both auto and other worked well as expected
//    std::set<Owner*>::iterator findOwner = ownerList.find(ow);
////    auto findowner = ownerList.find(new Owner(name));
//    if(findOwner == ownerList.end()){// if not found
//        delete ow;//avoid data leak, nur wenn Owner* ow = new Owner(name); separately defined.
//        return nullptr;
//    }
    int count = 0;
    for(auto& o : ownerList)
    {
        if (o->getName() == name)
        {
            count ++;
        }
    }
    if (count == 0){
        delete ow;
        return nullptr;
    }
    return ow;
}

bool FarmingSimulator::addPlot(int row, int col, const std::string &name, Plot *plot)
{
    if ( plot == nullptr ) {
        throw std::runtime_error("Plot is still available!");
        return false;
    }
    if ( getOwner(name) == nullptr ){
        throw std::invalid_argument("Owner does not exist!");
        return false;
    }
    plotList.at(row).at(col) = plot;
            plot->setRow(row); plot->setColumn(col);

    plot->setOwner(new Owner(name));
//    if (plot) //äquivalent zu if plot != nullptr (braucht man nicht)
//    {
//        plot->setRow(row); plot->setColumn(col);
//        plot->setOwner(new Owner(name));
//    }
    return true;
}

void FarmingSimulator::report()
{
    std::string ret = "";
    for (auto& s1 : plotList)
    {
        for (Plot* s2 : s1) //(auto& s2 : s1) geht auch, aber für die Klarheit wird Plot* genutzt
        {
            if (s2)
            {
                ret += "\nOwner's name: " + s2->getOwner()->getName() + "\n";
                ret += "At plot r: " + std::to_string(s2->getRow()) + " c: " + std::to_string(s2->getColumn()) + "\n";
                ret += "Art of Plot :";
                if (typeid(*s2) == typeid(Orchard))
                {
                    ret += "Orchard";
                    ret += "\nNumber of trees: " + std::to_string(dynamic_cast<Orchard*>(s2)->getTrees())+ "\n";
                }
                if (typeid(*s2).name() == typeid(Pasture).name())
                {
                    ret += "Pasture";
                    ret += "\nNumber of animals: " + std::to_string(dynamic_cast<Pasture*>(s2)->getAnimals())+ "\n";
                }

            }
            else ret += "Plot is empty\n";
        }
    }
    std::cout << ret << std::endl;
}

void FarmingSimulator::tick()
{
    for (auto& s1 : plotList)
    {
        for (Plot* s2 : s1) //(auto& s2 : s1) geht auch, aber für die Klarheit wird Plot* genutzt
        {
//            s2->tick();

            if (typeid(s2).name() == typeid(Orchard).name())
            {
                Orchard* orchard = dynamic_cast<Orchard*>(s2);
                orchard->tick();
            }
            if (typeid(s2).name() == typeid(Pasture).name())
            {
                Pasture* pas = dynamic_cast<Pasture*>(s2);
                pas->tick();
            }
        }
    }
}
/*
void FarmingSimulator::terminalUI()
{
    char button = ' ';
        std::string id_in;
        do {
            std::cout << "-----------MENU-----------" << std::endl;
            std::cout << "Enter <a> to add plot" << std::endl;
            std::cout << "Enter <r> to get all information" << std::endl;
            std::cout << "Enter <t> to activate the tick() methode" << std::endl;
            std::cout << "Enter <x/X> to exit" << std::endl;
            std::cout << "Please : "; std::cin >> button;
            std::cin.clear();
            std::cin.get();

            switch(button)
            {
            case 'A':
            case 'a': {
                int row, col;
                std::string name;

                addPlot(); break;
            }
            case 'i':
            case 'I': ; break;
            case 'c':
            case 'C': addCustomer(); break;
            case 'e':
            case 'E': addEmployee(); break;

            case 'f': std::cout << "Enter id "; std::cin >> id_in; find(id_in); break;
            case 'd': std::cout << "Enter id "; std::cin >> id_in; deleteCustomer(id_in); break;
            case 's': sortDatabase();break;

            default: break;
            }
        } while ( button != 'x' && button != 'X');
    }
}
*/
