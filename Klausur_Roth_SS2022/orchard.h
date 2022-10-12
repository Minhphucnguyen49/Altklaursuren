#ifndef ORCHARD_H
#define ORCHARD_H

#include "plot.h"


class Orchard : public Plot
{
public:
    Orchard(int row, int column, Owner *owner, int trees);
    Orchard(int row, int column, Owner *owner);
    Orchard(int trees);
    void tick() override;// trees = Anzahl von Bäume + (int)[Anzahl von Bäume/10]
    int getTrees() const;

private:
    int trees; // die Anzahl der gepflanzten Bäume repräsentiert.
};

#endif // ORCHARD_H
