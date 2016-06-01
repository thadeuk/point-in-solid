#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include "world.h"

vector<Point*> World::points;
vector<Polygon*> World::polygons;

int World::add_point(Point p)
{
    for (int i = 0; i < points.size(); i++) {
        if (*points[i] == p) {
            return i;
        }
    }
    points.push_back(new Point(p));
    return points.size()-1;
}

void World::add_triangle(Point p1, Point p2, Point p3)
{
    int p1_index = add_point(p1);
    int p2_index = add_point(p2);
    int p3_index = add_point(p3);
    Triangle *t = new Triangle(p1_index, p2_index, p3_index);
    polygons.push_back(t);
}

void World::add_triangle(int p1_idx, int p2_idx, int p3_idx)
{
    Triangle *t = new Triangle(p1_idx, p2_idx, p3_idx);
    polygons.push_back(t);
}

void World::add_rectangle(int p1_idx, int p2_idx, int p3_idx, int p4_idx)
{
    Rectangle *r = new Rectangle(p1_idx, p2_idx, p3_idx, p4_idx);
    polygons.push_back(r);
}

void World::create_world()
{
    srand(time(NULL));
    grid_max[0] = grid_max[1] = grid_max[2] = -99999;
    grid_min[0] = grid_min[1] = grid_min[2] = 99999;
    for (int i = 0; i < points.size(); i++) {
        grid_min[0] = min(grid_min[0], points[i]->x);
        grid_min[1] = min(grid_min[1], points[i]->y);
        grid_min[2] = min(grid_min[2], points[i]->z);
        grid_max[0] = max(grid_max[0], points[i]->x);
        grid_max[1] = max(grid_max[1], points[i]->y);
        grid_max[2] = max(grid_max[2], points[i]->z);
    }
}

/*
 * Return:
 *  0 if ray does not intersect.
 *  1 if ray degenerates.
 *  2 if ray intersect.
*/
int World::point_in_polygon(Point p, Point v)
{
    int intersections = 0;
    bool new_intersection_point;
    int ret;

    //v.print_point();
    for (int i = 0; i < polygons.size(); i++) {
        if (polygons[i]->contains_point(p)) {
            return 2;
        }

        ret = polygons[i]->ray_intersect(p, v);
        if (ret == 1) {
            return 1;
        }
        if (ret == 2) {
            intersections++;
        }
    }
    //cout << "Intersections = " << intersections << endl;
    return (intersections&1) ? 2 : 0; // odd number
}

Point World::get_random_point()
{
    double x = ((double) rand()/ (RAND_MAX))*2-1;
    double y = ((double) rand()/ (RAND_MAX))*2-1;
    double z = ((double) rand()/ (RAND_MAX))*2-1;
    return Point(x, y, z);
}


void World::normalize_points(double max_world)
{
    double min_value_x = 9999;
    double min_value_y = 9999;
    double min_value_z = 9999;

    double max_value = -9999;
    double max_value_x = -9999;
    double max_value_y = -9999;
    double max_value_z = -9999;

    for (int i = 0; i < points.size(); i++) {
        min_value_x = min(min_value_x, points[i]->x);
        min_value_y = min(min_value_y, points[i]->y);
        min_value_z = min(min_value_z, points[i]->z);

        max_value_x = max(max_value_x, points[i]->x);
        max_value_y = max(max_value_y, points[i]->y);
        max_value_z = max(max_value_z, points[i]->z);
    }

    cout << min_value_x << endl;
    cout << min_value_y << endl;
    cout << min_value_z << endl;
    if (min_value_x < 0) {
        max_value_x += -min_value_x+1;
        for (int i = 0; i < points.size(); i++)
            points[i]->x += -min_value_x+1;
    }
    if (min_value_y < 0) {
        max_value_y += -min_value_y+1;
        for (int i = 0; i < points.size(); i++)
            points[i]->y += -min_value_y+1;
    }
    if (min_value_z < 0) {
        max_value_z += -min_value_z+1;
        for (int i = 0; i < points.size(); i++)
            points[i]->z += -min_value_z+1;
    }

    max_value = max(max_value_x, max(max_value_y, max_value_z));

    double proportion = max_value/max_world;
    printf("max_value = %lf\nproportion = %lf\n", max_value, proportion);
    for (int i = 0; i < points.size(); i++) {
        points[i]->x /= proportion;
        points[i]->y /= proportion;
        points[i]->z /= proportion;
    }

    for (int i = 0; i < polygons.size(); i++) {
        polygons[i]->get_normal();
    }
}
