#include "stdafx.h"
#include "GVertex.h"



GVertex::GVertex(double x, double y) :
    GPoint(x, y)
{
}

GVertex::GVertex(GPoint &p) :
    GPoint(p)
{
}

GVertex *GVertex::cw(void)
{
    return (GVertex*)_next;
}

GVertex *GVertex::ccw(void)
{
    return (GVertex*)_prev;
}

GVertex *GVertex::neighbor(int rotation)
{
    return ((rotation == CLOCKWISE) ? cw() : ccw());
}

GPoint GVertex::point(void)
{
    return  *((GPoint*)this);
}

GVertex *GVertex::insert(GVertex *v)
{
    return (GVertex *)(GNode::insert(v));
}

GVertex *GVertex::remove(void)
{
    return (GVertex *)(GNode::remove());
}

void GVertex::splice(GVertex *b)
{
    GNode::splice(b);
}

GVertex *GVertex::split(GVertex *b)
{
    GVertex *bp = b->ccw()->insert(new GVertex(b->point()));
    insert(new GVertex(point()));

    splice(bp);
    return bp;
}
