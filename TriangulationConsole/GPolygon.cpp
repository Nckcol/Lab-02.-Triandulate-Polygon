#include "stdafx.h"
#include "GPolygon.h"



GPolygon::GPolygon() :
    _v(NULL), _size(0)
{
}

GPolygon::GPolygon(GPolygon &p) {
    _size = p._size;
    if (_size == 0)
        _v = NULL;
    else {
        _v = new GVertex(p.point());
        for (int i = 1; i < _size; i++) {
            p.advance(CLOCKWISE);
            _v = _v->insert(new GVertex(p.point()));
        }
        p.advance(CLOCKWISE);
        _v = _v->cw();
    }
}

GPolygon::GPolygon(GVertex *v) :
    _v(v)
{
    resize();
}

void GPolygon::resize(void)
{
    if (_v == NULL)
        _size = 0;
    else {
        GVertex *v = _v->cw();
        for (_size = 1; v != _v; ++_size, v = v->cw());
    }
}

GPolygon::~GPolygon(void)
{
    if (_v) {
        GVertex *w = _v->cw();
        while (_v != w) {
            delete w->remove();
            w = _v->cw();
        }
        delete _v;
    }
}

GVertex *GPolygon::v(void)
{
    return _v;
}

int GPolygon::size(void) const
{
    return _size;
}

GPoint GPolygon::point(void)
{
    return _v->point();
}

GEdge GPolygon::edge(void)
{
return GEdge(point(), _v->cw()->point());
}

GVertex *GPolygon::cw(void)
{
    return _v->cw();
}

GVertex *GPolygon::ccw(void)
{
    return _v->ccw();
}

GVertex *GPolygon::neighbor(int rotation)
{
    return _v->neighbor(rotation);
}

GVertex *GPolygon::advance(int rotation)
{
    return _v = _v->neighbor(rotation);
}

GVertex *GPolygon::setV(GVertex *v)
{
    return _v = v;
}

GVertex *GPolygon::insert(GPoint &p)
{
    if (_size++ == 0)
    {
        _v = new GVertex(p);
    }
    else
        _v = _v->insert(new GVertex(p));
    return _v;
}

void GPolygon::remove(void)
{
    GVertex *v = _v;
    _v = (--_size == 0) ? NULL : _v->ccw();
    delete v->remove();
}

GPolygon * GPolygon::split(GVertex * b)
{
    GVertex *bp = _v->split(b);
    resize();
    return new GPolygon(bp);
}

std::ostream & operator<<(std::ostream & os, const GPolygon & p)
{
    if (p._v == NULL)
        return os;
    
    GVertex *v = p._v->cw();
    os << *p._v;
    while(v != p._v)
    {
        os << *v;
        v = v->cw();
    }
    return os;
}
