#include "Vec3D.h"
#include <math.h>
Vec3D::Vec3D(double x_, double y_, double z_)
    :x(x_), y(y_), z(z_)
{}

Vec3D::Vec3D(double x_, double y_)
     :x(x_), y(y_), z(0)
{}

Vec3D::Vec3D(double x_)
    :x(x_), y(0), z(0)
{}

Vec3D::Vec3D()
    :x(0), y(0), z(0)
{}



Vec3D::~Vec3D()
{

}

double Vec3D::getX() const
{
    return x;
}

double Vec3D::getZ() const
{
    return z;
}

double Vec3D::getY() const
{
    return y;
}

double Vec3D::getLength() const
{
    double length = std::sqrt(x*x + y*y + z*z);
    return length;
}

double Vec3D::operator*(const Vec3D &right) const
{
    return (x*right.x + y*right.y + z*right.z);

}

Vec3D Vec3D::operator+(const Vec3D &right) const
{
    Vec3D a;
    a.x += right.x;
    a.y += right.y;
    a.z += right.z;
    return a;
}

Vec3D Vec3D::operator-(const Vec3D &right) const
{
    Vec3D a;
    a.x -= right.x;
    a.y -= right.y;
    a.z -= right.z;
    return a;
}

bool Vec3D::operator==(const Vec3D &right) const
{
    if ( x == right.x && y == right.y && z== right.z) {
        return true;
    }
    return false;
}
