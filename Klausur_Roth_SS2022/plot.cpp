#include "plot.h"

Plot::Plot(int row_, int column_, Owner *owner_)
    : row(row_),
    column(column_),
    owner(owner_)
{
//    this->row = row_;
//    this->column = column_;
//    this->owner = owner_;
}

int Plot::getRow() const
{
    return row;
}



int Plot::getColumn() const
{
    return column;
}


Owner *Plot::getOwner() const
{
    return owner;
}

void Plot::setRow(int newRow)
{
    row = newRow;
}

void Plot::setColumn(int newColumn)
{
    column = newColumn;
}

void Plot::setOwner(Owner *newOwner)
{
    owner = newOwner;
}




