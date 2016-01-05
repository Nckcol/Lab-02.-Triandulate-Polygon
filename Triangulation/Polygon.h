#pragma once

#include <cmath>
#include "Defines.h"

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

class GNode {
protected:
    GNode *_next;
    GNode *_prev;
public:
    GNode(void) : _next(this), _prev(this) {};
    virtual ~GNode(void) {};
    GNode *next(void)
    {
        return _next;
    }
    GNode *prev(void)
    {
        return _prev;
    }
    GNode *insert(GNode* node)
    {
        if (!_next)
        {
            _next = _prev = node;
            node->_next = node->_prev = this;
            return node;
        }

        node->_prev = this;
        node->_next = _next;

        _next->_prev = node;
        _next = node;

        return node;
    }

    GNode *remove(void)
    {
        _prev->_next = _next;
        _next->_prev = _prev;
        return this;
    }

    void splice(GNode * node)
    {
        GNode * b = node->_next;
        GNode * pa = this->_next;

        node->_next = pa;
        pa->_prev = node;

        _next = b;
        b->_prev = this;
    }
};

class GVertex : public GNode, public  GPoint {
public:
    GVertex(double x, double y);
    GVertex(GPoint&);
    GVertex *cw(void);
    GVertex *ccw(void);
    GVertex *neighbor(int rotation);
    GPoint point(void);
    GVertex *insert(GVertex*);
    GVertex *remove(void);
    void splice(GVertex*);
    GVertex *split(GVertex*);
    friend class GPolygon;
};

class GPolygon 
{

private:
    GVertex *_v;
    int _size;
    void resize(void);

public:
    GPolygon(void);
    GPolygon(GPolygon&);
    GPolygon(GVertex*);
    ~GPolygon(void);

    GVertex *v(void);
    int size(void) const;
    GPoint point(void);
    GEdge edge(void);
    GVertex *cw(void);
    GVertex *ccw(void);
    GVertex *neighbor(int rotation);
    GVertex *advance(int rotation);
    GVertex *setV(GVertex*);
    GVertex *insert(GPoint&);
    void remove(void);
    GPolygon * split(GVertex * b);

};
