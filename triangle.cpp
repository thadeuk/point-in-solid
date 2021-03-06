#include <cstdio>
#include "triangle.h"
#include "world.h"

Triangle::Triangle(int p1_idx, int p2_idx, int p3_idx)
{
    p1 = World::points[p1_idx];
    p2 = World::points[p2_idx];
    p3 = World::points[p3_idx];
    get_normal();
}

void
Triangle::print()
{
    p1->print();
    p2->print();
    p3->print();
}

/* Assume the point is inside the polygon */
bool
Triangle::is_in_border(const Point &p)
{
    if (p.are_collinear(*p1, *p2) || p.are_collinear(*p1, *p3) || p.are_collinear(*p2, *p3))
        return true;
    return false;
}

bool
Triangle::is_point_in_polygon(const Point &p)
{
    Point v0 = *p3 - *p1;
    Point v1 = *p2 - *p1;
    Point v2 = p - *p1;

    double dot00 = v0*v0;
    double dot01 = v0*v1;
    double dot02 = v0*v2;
    double dot11 = v1*v1;
    double dot12 = v1*v2;

    double invDenom = 1/(dot00 * dot11 - dot01 * dot01);
    double u = (dot11*dot02 - dot01*dot12)*invDenom;
    double v = (dot00*dot12 - dot01*dot02)*invDenom;
    return (u >= 0) && (v >= 0) && (u + v < 1);
}


bool
SameSide(const Point &p1, Point p2, Point a,  Point b)
{
    Point cp1 = (b-a)^(p1-a);
    Point cp2 = (b-a)^(p2-a);
    if (cp1*cp2 >= 0 ) return true;
    return false;

}

bool
Triangle::is_point_in_polygon2(const Point &p)
{
    if (SameSide(p, *p1, *p2, *p3) && SameSide(p, *p2, *p1, *p3) && SameSide(p, *p3, *p1, *p2)) {
        return true;
    }
    return false;
}


