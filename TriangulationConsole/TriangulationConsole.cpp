// TriangulationConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Defines.h"
#include "GPolygon.h"
#include <list>
#include <iostream> 

using namespace std;

list<GPolygon *> *triangulate(GPolygon  &p);
void findConvexVertex(GPolygon &p);
GVertex * findIntrudingVertex(GPolygon &p);
bool pointInTriangle(GPoint p, GPoint a, GPoint b, GPoint c);

int main()
{
    GPolygon mainPoly;

    /*mainPoly.insert(GPoint(0, 20));
    mainPoly.insert(GPoint(30, 10));
    mainPoly.insert(GPoint(10, 0));
    mainPoly.insert(GPoint(20, -10));*/
    //mainPoly.insert(GPoint(10, -20));
    //mainPoly.insert(GPoint(0, -10));
    //mainPoly.insert(GPoint(-30, -20));
    //mainPoly.insert(GPoint(0, 10));
    //mainPoly.insert(GPoint(-20, 10));

    /*
    mainPoly.insert(GPoint(-10, -10));
    mainPoly.insert(GPoint(-10, 10));
    mainPoly.insert(GPoint(0, 0));
    mainPoly.insert(GPoint(10, 10));
    mainPoly.insert(GPoint(10, -10));*/



    mainPoly.insert(GPoint(-200, 500));
    mainPoly.insert(GPoint(-100, 300));
    mainPoly.insert(GPoint(0, 400));
    //mainPoly.insert(GPoint(0, 500));
    //mainPoly.insert(GPoint(200, 400));
    mainPoly.insert(GPoint(200, 300));
    mainPoly.insert(GPoint(100, 0));
    mainPoly.insert(GPoint(0, 100));
    //mainPoly.insert(GPoint(-200, 0));
    
    
    

    //cout << mainPoly << endl;

    //cout << *mainPoly.v()->cw() << endl;

    //GPolygon * second = mainPoly.split(mainPoly.v()->cw()->cw());

    //cout << mainPoly << endl;
    //cout << *second << endl;

    list < GPolygon * > * triangles = triangulate(mainPoly);

    for (auto i = triangles->begin(); i != triangles->end(); i++)
    {
        cout << **i << endl;
    }

    return 0;
}


list<GPolygon *> *triangulate(GPolygon  &p)
{
    list<GPolygon*> *triangles = new list<GPolygon*>;
    if (p.size() == 3)
        triangles->push_back(&p);
    else {
        findConvexVertex(p);
        GVertex *d = findIntrudingVertex(p);
        if (d == NULL) {        // ??? ???????????? ??????
            GVertex  *c = p.neighbor(CLOCKWISE);
            p.advance(COUNTER_CLOCKWISE);
            GPolygon *q = p.split(c);
            triangles->merge(*triangulate(p));
            triangles->push_back(q);
        }
        else {                  // d - ???????????? ???????
            GPolygon   *q = p.split(d);
            triangles->merge(*triangulate(*q));
            triangles->merge(*triangulate(p));
        }
    }
    return triangles;
}

void findConvexVertex(GPolygon &p)
{
    GVertex *a = p.neighbor(COUNTER_CLOCKWISE);
    GVertex *b = p.v();
    GVertex *c = p.neighbor(CLOCKWISE);
    while (c->classify(*a, *b) != RIGHT) {
        a = b;
        b = p.advance(CLOCKWISE);
        c = p.neighbor(CLOCKWISE);
    }
}

GVertex * findIntrudingVertex(GPolygon &p)
{
    GVertex *a = p.neighbor(COUNTER_CLOCKWISE);
    GVertex *b = p.v();
    GVertex *c = p.advance(CLOCKWISE);
    GVertex *d = NULL;     // ?????? ???????? ?? ?????? ??????
    double bestD = -1.0;  // ?????????? ?? ??????? ?????????
    GEdge ca(c->point(), a->point());
    GVertex *v = p.advance(CLOCKWISE);
    while (v != a) {
        if (pointInTriangle(*v, *a, *b, *c)) {
            double dist = v->distance(ca);
            if (dist > bestD) {
                d = v;
                bestD = dist;
            }
        }
        v = p.advance(CLOCKWISE);
    }
    p.setV(b);
    return d;
}

bool pointInTriangle(GPoint p, GPoint a, GPoint b, GPoint c)
{
    return ((p.classify(a, b) != LEFT) &&
        (p.classify(b, c) != LEFT) &&
        (p.classify(c, a) != LEFT));
}

