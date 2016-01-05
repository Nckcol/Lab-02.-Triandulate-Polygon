#pragma once

#include <iostream>
#include "GPoint.h"

class GNode {
protected:
    GNode *_next;
    GNode *_prev;
public:
    GNode(void): _next(this), _prev(this) {};
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

