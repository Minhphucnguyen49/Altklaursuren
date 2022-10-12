#ifndef PASTURE_H
#define PASTURE_H

#include "plot.h"


class Pasture : public Plot
{
public:
    Pasture(int row, int column, Owner *owner, int animals);
    Pasture(int row, int column, Owner *owner);
    Pasture(int animals);
    void tick() override;
    int getAnimals() const;

private:
    int animals;// die Anzahl der Tiere repräsentiert.

};

#endif // PASTURE_H
