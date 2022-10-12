/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Universe.cpp
 * Author: mroth
 *
 * Created on 3. September 2018, 11:09
 */

#include "Universe.h"
#include "fstream"
#include "sstream"
#include "algorithm"

/*
 * Erklaerung der Rueckgabewerte:
 * Damit die Vorgabedateien ganz normal compilen und auch ohne Laufzeitfehler ausfuehrbar sind,
 * wurden bei Methoden die Rueckgaben erfordern Dummy Werte eingefuegt.
 * Diese muessen Sie entfernen, wenn Sie die entsprechenden Methoden implementieren.
 */
//"stars-utf8.txt"
/*
    Implementieren Sie den Konstruktor und lesen Sie dort erfolgreich die 247 Sterne aus der
    Textdatei ein und speichern diese in einem Container Ihrer Wahl in der Klasse Universe ab.
*/
Universe::Universe(const std::string& starsFileName)
{
    std::fstream file(starsFileName);
    if ( !file.good() )
    {
        throw ("file can not be opened");
    }
    std::string line;

    getline(file, line);//read and discard the first line
    while(!file.eof())
    {
        getline(file, line, '\n');
        if (file.eof())
        {
            return;
//            throw std::invalid_argument("The file is read successfully!");
        }

        std::stringstream tmp(line);
        std::string col;

        //read the first column - ID
        getline (tmp, col, ';'); int id = std::stoi(col);

        getline (tmp, col, ';'); std::string name;
        if(col != "")
        {
            name = col;
        }else name = "";

        getline (tmp, col, ';');
        double x = std::stod(col);

        getline (tmp, col, ';');
        double y = std::stod(col);

        getline (tmp, col, ';');
        double z = std::stod(col);

        Vec3D pos(x,y,z);

        getline (tmp, col, ';');
        std::string constellation;
        constellation = col;
        if(col != "")
        {
            constellation = col;
        } else constellation = "";

        Star* s = new Star(id, name, pos, constellation);
        starList.push_back(s);
    }
}

Universe::~Universe()
{
    for(Star* s : starList)
    {
        delete s;
    }
}

std::list<Universe::Distance> Universe::getAllDistances() const
{
    std::list<Distance> starDis;
    Distance d;
    for(Star* s1 : starList)
    {
        for(Star* s2 : starList)
        {
            if (s1->getId() != s2->getId())
            {
                d.a = s1;
                d.b = s2;
                d.distance = (s1->getPos()-s2->getPos()).getLength();
                starDis.push_back(d);
            }
            else continue;
        }
    }

    return std::list<Distance>(starDis);
}

std::list<Star*> Universe::getStarsSortedByDistanceToEarth() const
{
    std::vector<Star*> starDis;
    for(Star* s : starList)
    {
        starDis.push_back(s);
    }

    std::sort(starDis.begin(), starDis.end(),
              [](const Star* lhs, const Star* rhs)
                {
                    double lhs_dis = lhs->getPos().getLength();
                    double rhs_dis = rhs->getPos().getLength();
                    return lhs_dis < rhs_dis;
                }
             );
    std::list<Star*> starList_return;
    for(Star* s : starDis)
    {
        starList_return.push_back(s);
    }
    return std::list<Star*>(starList_return);
}

/*
 *
    Implementieren Sie die Methode getStarsSortedByName, die eine nach Namen des Sterns
    sortierte Liste zur ̧ck geben soll.
    Die Liste soll Zeiger auf die Sterne in der korrekten Reihenfolge beinhalten.
    Sterne, die keinen Namen besitzen, sollen in dieser Liste nicht erscheinen
*/

std::list<Star*> Universe::getStarsSortedByName() const
//void Universe::getStarsSortedByName() const
{
    std::vector<Star*> starVec;
//    std::list<Star*> starVec; to use list, maybe I have to use the sort function for list, sth like std::list::sort
    for(Star* s : starList)
    {
        if( s->getName() == "" )
        {
            continue;
        }
        starVec.push_back(s);
    }
    std::sort(starVec.begin(), starVec.end(),//this only works with vector
              [](const Star* lhs, const Star* rhs)
                { return lhs->getName() < rhs->getName(); }
             );
    std::list<Star*> starList_return;

    for(Star* s : starVec)
    {
        starList_return.push_back(s);
    }
//    Printing the sorted list
//    std::string rt = "";
//    for(Star* s : starList_return)
//    {
//        rt += s->getName() + "; ";
//        std::cout << rt << std::endl;
//        rt = "";
//    }
//    return std::list<Star*>(starVec);
    return std::list<Star*>(starList_return);
}

std::list<Star*> Universe::getStarsInRadius(const Vec3D& pos, double radius)
{
    return std::list<Star*>();
}

int Universe::getNearestStar(const Vec3D& pos)
{
    return -1;
}

/*
 * Implementieren Sie getStarById so, dass die Methode einen Zeiger auf den Stern mit der
   bergebenen ID zurueck gibt.
   Gibt es keinen Stern mit dieser ID, so geben Sie einen nullptr
   zurueck.
*/
Star* Universe::getStarById(int id)
{
    for(Star* s : starList)
    {
        if (s->getId() == id)
            return s;
    }
    return nullptr;
}

void Universe::menu() const
{
    std::string rt = "";
    rt += "Enter <p> to print out star list\n";
    rt += "Enter <n> to sort by name\n";
    rt += "Enter <e> to sort by distance to earth\n";
    rt += "Enter <e> to get all distances\n";
    rt += "Enter <x> to exit";

    char button = ' ';
    do{
        std::cout << rt << std::endl;
        std::cin >> button;
        switch(button)
        {
        case 'P':
        case 'p': printList(starList);break;
        case 'n': printList(getStarsSortedByName()); break;
        case 'e': printList(getStarsSortedByDistanceToEarth()); break;
        case 'd': printListofDistance(getAllDistances());
        case 'x':
        case 'X': return;
        default: break;
        }
    } while (true);
}

void Universe::printListofDistance(const std::list<Distance>& list) const
{
    std::string rt;
    for(const Distance& d : list)
    {
        rt += "Distance from star with ID " + std::to_string(d.a->getId());
        rt += " to star with ID " + std::to_string(d.b->getId()) + " is ";
        rt += std::to_string(d.distance);
        std::cout << rt << std::endl;
        rt = "";
    }
}
void Universe::printList(const std::list<Star*>& list) const
{
    std::string rt;
    for(Star* s : list)
    {
        rt += std::to_string(s->getId()) + ";";
        rt += s->getName() + ";";
        rt += std::to_string(s->getPos().getX()) + ";";
        rt += std::to_string(s->getPos().getY()) + ";";
        rt += std::to_string(s->getPos().getZ()) + ";";
        rt += s->getConstellation();
        std::cout << rt << std::endl;
        rt = "";
    }
}
std::list<Star*> Universe::getPathTo(const Vec3D& from, const Vec3D& to, double maxHop)
{
    return std::list<Star*>();
}






