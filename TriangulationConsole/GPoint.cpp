#include "stdafx.h"
#include "GPoint.h"

GPoint::GPoint(double _x, double _y) :
    x(_x), y(_y)
{
}

GPoint GPoint::operator+ (GPoint &p)
{
    return GPoint(x + p.x, y + p.y);
}

GPoint GPoint::operator- (GPoint &p)
{
    return GPoint(x - p.x, y - p.y);
}

GPoint operator* (double s, GPoint &p)
{
    return GPoint(s * p.x, s * p.y);
}

double GPoint::operator [] (int i)
{
    return (i == 0) ? x : y;
}

int GPoint::operator== (GPoint &p)
{
    return (x == p.x) && (y == p.y);
}

int GPoint::operator!= (GPoint &p)
{
    return !(*this == p);
}

int GPoint::operator< (GPoint &p)
{
    return ((x < p.x) || ((x == p.x) && (y<p.y)));
}

int GPoint::operator> (GPoint &p)
{
    return ((x>p.x) || ((x == p.x) && (y > p.y)));
}

int orientation(GPoint &p0, GPoint &p1, GPoint &p2)
{
    GPoint a = p1 - p0;
    GPoint b = p2 - p0;
    double sa = a.x * b.y - b.x * a.y;
    if (sa > 0.0)
        return 1;
    if (sa < 0.0)
        return -1;
    return 0;
}

int GPoint::classify(GPoint &p0, GPoint &p1)
{
    GPoint p2 = *this;
    GPoint a = p1 - p0;
    GPoint b = p2 - p0;
    double sa = a.x * b.y - b.x * a.y;
    if (sa > 0.0)
        return LEFT;
    if (sa < 0.0)
        return RIGHT;
    if ((a.x * b.x < 0.0) || (a.y * b.y < 0.0))
        return BEHIND;
    if (a.length() < b.length())
        return BEYOND;
    if (p0 == p2)
        return ORIGIN;
    if (p1 == p2)
        return DESTINATION;
    return BETWEEN;
}


int GPoint::classify(GEdge &e)
{
    return classify(e.org, e.dest);
}

double GPoint::polarAngle(void)
{
    if ((x == 0.0) && (y == 0.0))
        return -1.0;
    if (x == 0.0)
        return ((y > 0.0) ? 90 : 270);
    double theta = atan(y / x);
    theta *= 360 / (2 * 3.1415926);
    if (x > 0.0)
        return ((y >= 0.0) ? theta : 360 + theta);
    else
        return (180 + theta);
}

double GPoint::length(void)
{
    return sqrt(x*x + y*y);
}


double GPoint::distance(GEdge &e)
{
    GEdge ab = e;
    ab.flip().rot();

    GPoint n(ab.dest - ab.org);
    n = (1.0 / n.length()) * n;
    GEdge f(*this, *this + n);

    double t;
    f.intersect(e, t);
    return t;
}

GEdge::GEdge(GPoint &_org, GPoint &_dest) :
    org(_org), dest(_dest)
{
}

GEdge::GEdge() :
    org(GPoint(0, 0)), dest(GPoint(1, 0))
{
}

GEdge &GEdge::rot()
{
    GPoint m = 0.5 * (org + dest);
    GPoint v = dest - org;
    GPoint n(v.y, -v.x);
    org = m - 0.5 * n;
    dest = m + 0.5 * n;
    return *this;
}

GEdge &GEdge::flip()
{
    return rot().rot();
}

GPoint GEdge::point(double t)
{
    return GPoint(org + t * (dest - org));
}

double dotProduct(GPoint &p, GPoint &q)
{
    return (p.x * q.x + p.y * q.y);
}


int GEdge::intersect(GEdge &e, double &t)
{
    GPoint a = org;
    GPoint b = dest;
    GPoint c = e.org;
    GPoint d = e.dest;
    GPoint n = GPoint((d - c).y, (c - d).x);
    double denom = dotProduct(n, b - a);
    if (denom == 0.0) {
        int aclass = org.classify(e);
        if ((aclass == LEFT) || (aclass == RIGHT))
            return PARALLEL;
        else return COLLINEAR;
    }
    double num = dotProduct(n, a - c);
    t = -num / denom;
    return SKEW;
}


int GEdge::cross(GEdge &e, double &t)
{
    double s;
    int crossType = e.intersect(*this, s);
    if ((crossType == COLLINEAR) || (crossType == PARALLEL))
        return crossType;
    if ((s < 0.0) || (s > 1.0))
        return SKEW_NO_CROSS;
    intersect(e, t);
    if ((0.0 <= t) && (t <= 1.0))
        return SKEW_CROSS;
    else
        return SKEW_NO_CROSS;
}


bool GEdge::isVertical(void)
{
    return (org.x == dest.x);
}

double GEdge::slope(void)
{
    if (org.x != dest.x)
        return (dest.y - org.y) / (dest.x - org.x);
    return INFINITY;
}

double GEdge::y(double x)
{
    return slope() * (x - org.x) + org.y;
}

std::ostream & operator<<(std::ostream & os, const GPoint & p)
{
    os << "(" << p.x << "," << p.y << ")";
    return os;
}