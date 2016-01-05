#pragma once

#include "Defines.h"
#include <cmath>
#include <iostream>

class GEdge;

class GPoint
{

public:


    double x;
    double y;

    GPoint(double _x = 0.0, double _y = 0.0);

    GPoint operator+(GPoint &);
    GPoint operator-(GPoint &);
    friend GPoint operator* (double, GPoint &);

    double operator[] (int);

    int operator== (GPoint &);
    int operator!= (GPoint &);

    int operator< (GPoint &);
    int operator> (GPoint &);

    int classify(GPoint &, GPoint &);
    int classify(GEdge &);

    double polarAngle(void);

    double length(void);

    double distance(GEdge &);

    friend std::ostream & operator<<(std::ostream & os, const GPoint & p);
};

class GEdge {

public:

    GPoint org;
    GPoint dest;

    GEdge(GPoint &_org, GPoint &_dest);
    GEdge(void);
    GEdge &rot(void);
    GEdge &flip(void);
    GPoint point(double);
    int intersect(GEdge&, double&);
    int cross(GEdge&, double&);
    bool isVertical(void);
    double slope(void);
    double y(double);
};
