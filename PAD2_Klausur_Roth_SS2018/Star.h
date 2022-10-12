/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Star.h
 * Author: mroth
 *
 * Created on 3. September 2018, 11:04
 */

#ifndef STAR_H
#define STAR_H
#include <string>
#include "iostream"
#include "Vec3D.h"

class Star
{
public:
    Star(int id, const std::string& name, const Vec3D& pos, const std::string& constellation);

    bool operator==(const Star& right) const;
    virtual ~Star();

    int getId() const;
    std::string getName() const;
    Vec3D getPos() const;
    std::string getConstellation() const;

private:
    //Platz fuer Ihre Attribute
    int ID;
    std::string name;
    Vec3D position;
    std::string constellation;//Sternbild
};

#endif /* STAR_H */

