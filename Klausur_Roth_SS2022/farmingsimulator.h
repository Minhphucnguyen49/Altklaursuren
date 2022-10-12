#ifndef FARMINGSIMULATOR_H
#define FARMINGSIMULATOR_H

#include "owner.h"
#include "plot.h"
#include <set>
#include <vector>
#include "orchard.h"
#include "pasture.h"

class FarmingSimulator
{
public:
    FarmingSimulator(int rows, int columns);
    bool createOwner(const std::string& name);
    Owner* getOwner(const std::string& name);
    bool addPlot(int row, int col, const std::string& name, Plot* plot);
    void report();
    void tick();
    void terminalUI();
private:
    //Einen Container zum Speichern von Besitzern (Objekte von oder Zeiger auf Owner)
    std::set<Owner*> ownerList;
    //Einen Container zum Speichern der Parzellen (Zeiger auf Plot)
    std::vector<std::vector<Plot*>> plotList;
};

#endif // FARMINGSIMULATOR_H
