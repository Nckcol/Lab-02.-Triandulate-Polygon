#pragma once

#include <iostream>
#include "GVertex.h"

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

    friend std::ostream & operator<<(std::ostream & os, const GPolygon & p);
};

