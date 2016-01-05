#pragma once

#include "resource.h"
#include "Defines.h"
#include "Polygon.h"
#include <list>

using namespace std;

void init();
void draw(HDC hdc);
list<GPolygon *> *triangulate(GPolygon  &p);
void findConvexVertex(GPolygon &p);
GVertex * findIntrudingVertex(GPolygon &p);
bool pointInTriangle(GPoint p, GPoint a, GPoint b, GPoint c);