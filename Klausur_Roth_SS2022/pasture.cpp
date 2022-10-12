#include "pasture.h"

Pasture::Pasture(int row, int column, Owner *owner, int animals)
    :Plot(row, column, owner), animals(animals)
{}

Pasture::Pasture(int row, int column, Owner *owner)
:Plot(row, column, owner)
{}

Pasture::Pasture(int animals_)
    :Plot(row, column, owner),animals(animals_)
{}

void Pasture::tick()// animals = anzahl Tiere + (int)(anzahl Tiere/2)
{
    animals += (int)(animals/2);
}

int Pasture::getAnimals() const
{
    return animals;
}



