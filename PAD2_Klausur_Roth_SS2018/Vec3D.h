/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Vec3D.h
 * Author: mroth
 *
 * Created on 31. August 2018, 15:07
 */

#ifndef VEC3D_H
#define VEC3D_H

class Vec3D
{
public:
    Vec3D(double x, double y, double z);
    Vec3D(double x, double y);
    Vec3D(double x);
    Vec3D();
    //evtl. werden weitere Konstruktoren benoetigt

    double getLength() const;

    double operator*(const Vec3D& right) const;

    Vec3D operator+(const Vec3D& right) const;

    Vec3D operator-(const Vec3D& right) const;

    bool operator==(const Vec3D& right) const;

    virtual ~Vec3D();
    double getX() const;

    double getZ() const;

    double getY() const;

private:
    //Platz fuer Ihre Attribute
    double x, y, z;
};

#endif /* VEC3D_H */

