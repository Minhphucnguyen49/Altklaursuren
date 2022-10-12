#ifndef PLOT_H
#define PLOT_H

#include "owner.h"

class Plot
{
public:
    Plot(int row, int column, Owner *owner);
    virtual ~Plot() = default;

    virtual void tick() = 0; //pure virtual methode(rein virtuelle Methode der Klasse Plot)
    int getRow() const;
    int getColumn() const;

    Owner *getOwner() const;

    void setRow(int newRow);
    void setColumn(int newColumn);
    void setOwner(Owner *newOwner);

protected:
    int row, column;
    Owner* owner;//speichert einen Zeiger auf den Besitzer (Instanz von Owner) dieser Parzelle
};

#endif // PLOT_H
