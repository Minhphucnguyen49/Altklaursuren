/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Universe.h
 * Author: mroth
 *
 * Created on 3. September 2018, 11:09
 */

#ifndef UNIVERSE_H
#define UNIVERSE_H
#include "Star.h"
#include <string>
#include <list>

class Universe
{
public:
    //Dieses struct speichert Distanzen zwischen jeweils zwei Sternen. Muss
    // zumindest fuer die Aufgabe getAllDistances verwendet werden.
    // Sie koennen bei Bedarf das struct erweitern, aber bestehende Inhalte duerfen nicht veraendert werden.
    struct Distance
    {
        Star* a;
        Star* b;
        double distance;
    };

    Universe(const std::string& starsFileName);

    virtual ~Universe();

    std::list<Star*> getStarsSortedByName() const;

    std::list<Star*> getStarsSortedByDistanceToEarth() const;

    std::list<Distance> getAllDistances() const;

    int getNearestStar(const Vec3D& pos);

    std::list<Star*> getStarsInRadius(const Vec3D& pos, double radius);

    std::list<Star*> getPathTo(const Vec3D& from, const Vec3D& to, double maxHop);

    Star* getStarById(int id);

    void menu() const;
    void printList(const std::list<Star*>& ) const;
    //void getStarsSortedByName() const;

    void printListofDistance(const std::list<Distance> &list) const;
private:
    //Platz fuer Ihre Attribute
    std::list<Distance> starDistances;//can not use this because of const problem
    std::list<Star*> starList;
};

#endif /* UNIVERSE_H */

