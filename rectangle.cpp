#include <cstdio>
#include "rectangle.h"
#include "world.h"

Rectangle::Rectangle(int p1_idx, int p2_idx, int p3_idx, int p4_idx)
{
    p1 = World::points[p1_idx];
    p2 = World::points[p2_idx];
    p3 = World::points[p3_idx];
    p4 = World::points[p4_idx];
    get_normal();
}

void
Rectangle::print_points()
{
    p1->print_point();
    p2->print_point();
    p3->print_point();
    p4->print_point();
}


/* Assume the point is inside the polygon */
bool
Rectangle::is_in_border(const Point &p)
{
    if (p.are_collinear(*p1, *p2) || p.are_collinear(*p1, *p3) || p.are_collinear(*p2, *p3) || p.are_collinear(*p4, *p1))
        return true;
    return false;
}

bool Rectangle::is_same_side(Point p1, Point p2, Point a,  Point b)
{
    Point cp1 = (p2-p1)^(a-p1);
    Point cp2 = (p2-p1)^(b-p1);
    if (cp1*cp2 >= 0)
        return true;
    return false;
}

bool
Rectangle::is_point_in_polygon(const Point &p)
{
    if (is_same_side(*p1, *p2, *p3, p) && 
        is_same_side(*p2, *p3, *p4, p) && 
        is_same_side(*p3, *p4, *p1, p) && 
        is_same_side(*p4, *p1, *p2, p))
        return true;

    return false;  
}


