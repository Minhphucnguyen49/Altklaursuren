#include "Star.h"

Star::Star(int id, const std::string &name, const Vec3D &pos, const std::string &constellation)
    : ID(id), name(name), position(pos), constellation(constellation)
{

}

Star::~Star()
{

}

int Star::getId() const
{
    return ID;
}

std::string Star::getName() const
{
    return name;
}

Vec3D Star::getPos() const
{
    return position;

}

std::string Star::getConstellation() const
{
    return constellation;

}

