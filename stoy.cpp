#include <fstream>
#include "world.h"
#include "stoy.h"
#define INF 100000

using namespace std;

void BrickList::readBrickFromCSG(string path)
{
    ifstream my_file(path);
    string line; 
    float t1, t2, t3, c1, c2, c3;
    while (getline(my_file, line)) {
        size_t pos = line.find("translate([");
        if (pos != string::npos) {
            sscanf(line.c_str() + pos+11,"%f, %f, %f])  cube([%f, %f, %f ", &t1, &t2, &t3, &c1, &c2, &c3);
            bricks.push_back(Brick(t1, t2, t3, t1+c1, t2+c2, t3+c3));
        }
    }
}

void BrickList::createList(World &w, double side_size)
{
    int ret;

    for (double x = w.grid_min[0];  x < w.grid_max[0]; x += side_size) {
        for (double y = w.grid_min[1]; y < w.grid_max[1]; y += side_size) {
                for (double z = w.grid_min[2]; z < w.grid_max[2]; z += side_size) {
                Point p(x+side_size/2., y+side_size/2., z + side_size/2.);
                while ((ret = w.point_in_polygon(p, w.get_random_point() )) == 1);
                if (ret == 2) {
                    bricks.push_back(Brick(x, y, z, side_size));    
                }
            }
        }
    }
}


void BrickList::joinBricks() {
    for (auto it = bricks.begin(); it != bricks.end(); it++) {
        for (auto it2 = bricks.begin(); it2 != bricks.end(); it2++) {
            if (it == it2) continue;

            if ((*it).share_x_face(*it2)) {
                Brick b(min(it->lowerx, it2->lowerx), it->lowery, it->lowerz, max(it->upperx, it2->upperx), it->uppery, it->upperz);
                bricks.erase(it);
                bricks.erase(it2);
                bricks.push_back(b);
                it = bricks.begin();
                it2 = bricks.begin();
            }
            else if ((*it).share_y_face(*it2)) {
                Brick b(it->lowerx, min(it->lowery, it2->lowery), it->lowerz, it->upperx, max(it->uppery, it2->uppery), it->upperz);
                bricks.erase(it);
                bricks.erase(it2);
                bricks.push_back(b);
                it = bricks.begin();
                it2 = bricks.begin();
            }
            else if ((*it).share_z_face(*it2)) {
                Brick b(it->lowerx, it->lowery, min(it->lowerz, it2->lowerz), it->upperx, it->uppery, max(it->upperz, it2->upperz));
                bricks.erase(it);
                bricks.erase(it2);
                bricks.push_back(b);
                it = bricks.begin();
                it2 = bricks.begin();
            }
            else if ((*it).is_inside(*it2)) {
                it = bricks.erase(it);
            }
        }
    }

}

void BrickList::printCSG()
{
    for (auto it = bricks.begin(); it != bricks.end(); it++) {
        it->printCSG();
    }
}

void BrickList::print()
{
    for (auto it = bricks.begin(); it != bricks.end(); it++) {
        it->printRaw();
    }
}

bool BrickList::isInside(Point &point)
{
    for (auto it = bricks.begin(); it != bricks.end(); it++) {
        if (it->isInside(point))
            return true;
    }
    return false;
}


