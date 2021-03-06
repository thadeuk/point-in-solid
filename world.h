#pragma once
#include <vector>
#include "polygon.h"
#include "geometrics.h"
#include "triangle.h"
#include "rectangle.h"

using namespace std;

class World
{
public:
    static vector<Point*> points;
    static vector<Polygon*> polygons;

    int add_point(Point p);
    void add_triangle(Point p1, Point p2, Point p3);
    void add_triangle(int p1_idx, int p2_idx, int p3_idx);
    void add_rectangle(int p1_idx, int p2_idx, int p3_idx, int p4_idx);

    void create_world();
    int point_in_polygon(Point p, Point v);
    void normalize_points(double max_world);
    Point get_random_point();

    double grid_max[3]; // x, y, z
    double grid_min[3];

};
