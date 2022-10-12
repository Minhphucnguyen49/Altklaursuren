#include "orchard.h"


Orchard::Orchard(int row, int column, Owner *owner, int trees)
    :Plot(row, column, owner), trees(trees)
{

}

Orchard::Orchard(int row, int column, Owner *owner)
    :Plot(row, column, owner)
{

}

Orchard::Orchard(int trees_)
    :Plot(row, column, owner), trees(trees_)
{

}
// trees = Anzahl von Bäume + (int)[Anzahl von Bäume/10]
void Orchard::tick()
{
    trees += (int)(trees/10);

}

int Orchard::getTrees() const
{
    return trees;
}


