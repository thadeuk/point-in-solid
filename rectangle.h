#pragma once
#include "geometrics.h"
#include "polygon.h"

class Rectangle : public Polygon
{
private:
    Point *p4;

public:
    Rectangle(int _p1_idx, int _p2_idx, int _p3_idx, int _p4_idx);

    void print_points();
    bool is_in_border(const Point &);
    bool is_point_in_polygon(const Point &);
    bool is_same_side(Point p1, Point p2, Point a, Point b);
};

