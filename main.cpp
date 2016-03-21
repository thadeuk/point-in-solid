#include <iostream>
#include <cstdio>
#include <limits>
#include <algorithm>
#include <fstream>
#include <list>
#include "world.h"
#include "obj_file.h"
#define EPSILON 1E-5
#define INF 100000

using namespace std;
bool IsLess(double a, double b)
{
    return b - a > EPSILON;
}

bool AreEqual(double a, double b)
{
    return fabs(a - b) < EPSILON;
}

double lessd(double a, double b)
{
    a < b ? a : b;
}

double greaterd(double a, double b)
{
    a > b ? a : b;
}

class Brick
{

public:
    double lowerx, lowery, lowerz;
    double upperx, uppery, upperz;
    Brick(double x, double y, double z, double side_size) {
        lowerx = x;
        lowery = y;
        lowerz = z;
        upperx = x + side_size;
        uppery = y + side_size;
        upperz = z + side_size;
    }

    Brick(const double& lx, const double& ly, const double& lz, const double& ux, const double& uy, const double& uz) {
        lowerx = lx;
        lowery = ly;
        lowerz = lz;
        upperx = ux;
        uppery = uy;
        upperz = uz;
    }

    void printCSG() {
        cout << "translate([" << lowerx << "," << lowery << "," << lowerz << "])";
        cout << "\tcube(["<< upperx-lowerx << "," << uppery-lowery << "," << upperz-lowerz << "]);" << endl;
    }
    void print() {
        cout << "(" << lowerx << "," << lowery << "," << lowerz << "),(" << upperx << "," << uppery << "," << upperz << ")" << endl;
    }
    void printRaw() {
        cout << lowerx << " " << lowery << " " << lowerz << endl;
        cout << upperx << " " << uppery << " " << upperz << endl;
    }

    bool equal_x(Brick &b) {
        if (AreEqual(lowerx, b.lowerx) && AreEqual(upperx, b.upperx)) return true;
        return false;
    }
    bool equal_y(Brick &b) {
        if (AreEqual(lowery, b.lowery) && AreEqual(uppery, b.uppery)) return true;
        return false;
    }
    bool equal_z(Brick &b) {
        if (AreEqual(lowerz, b.lowerz) && AreEqual(upperz, b.upperz)) return true;
        return false;
    }

    bool equal_xy(Brick &b) {
        if (equal_x(b) && equal_y(b))
            return true;
        return false;
    }
    bool equal_xz(Brick &b) {
        if (equal_x(b) && equal_z(b))
            return true;
        return false;
    }
    bool equal_yz(Brick &b) {
        if (equal_y(b) && equal_z(b))
            return true;
        return false;
    }

    bool share_x_face(Brick &b) {
        if ((AreEqual(upperx, b.lowerx) || AreEqual(lowerx, b.upperx)) && equal_yz(b))
            return true;
        return false;
    }

    bool share_y_face(Brick &b) {
        if ((AreEqual(uppery, b.lowery) || AreEqual(lowery, b.uppery)) && equal_xz(b))
            return true;
        return false;
    }

    bool share_z_face(Brick &b) {
        if ((AreEqual(upperz, b.lowerz) || AreEqual(lowerz, b.upperz)) && equal_xy(b))
            return true;
        return false;
    }

    bool is_inside(Brick &b) {
        if (lowerx >= b.lowerx && upperx <= b.upperx &&
                lowery >= b.lowery && uppery <= b.uppery &&
                lowerz >= b.lowerz && upperz <= b.upperz)
            return true;
        return false;
    }
    
};

list<Brick> bricks;


void run(World &w)
{
    int outside = 0;
    int inside = 0;
    int undefined = 0;


    int ret;
    double side_size = 2.01;
    double initial_point = -35;
    double end_point = 35;
    int t = 0;

    double min_xyz[3] = {INF, INF, INF};
    double max_xyz[3] = {-INF, -INF, -INF};

    for (double x = initial_point; IsLess(x, end_point); x += side_size) {
        for (double y = initial_point; IsLess(y, end_point); y += side_size) {
            for (double z = initial_point; IsLess(z, end_point); z += side_size) {
                Point p(x+side_size/2., y+side_size/2., z + side_size/2.);
                while ((ret = w.point_in_polygon(p, w.get_random_point() )) == 1);
                if (ret == 2) {
                    if (min_xyz[0] > x) min_xyz[0] = x;
                    if (min_xyz[1] > y) min_xyz[1] = y;
                    if (min_xyz[2] > z) min_xyz[2] = z;
                    if (max_xyz[0] < x+side_size) max_xyz[0] = x+side_size;
                    if (max_xyz[1] < y+side_size) max_xyz[1] = y+side_size;
                    if (max_xyz[2] < z+side_size) max_xyz[2] = z+side_size;
                    bricks.push_back(Brick(x, y, z, side_size));    
                }
                t++;
            }
        }
    }
    cout << "MIN = " << min_xyz[0] << ", " << min_xyz[1] << ", " << min_xyz[2] << endl;
    cout << "MAX = " << max_xyz[0] << ", " << max_xyz[1] << ", " << max_xyz[2] << endl;
}

int
main()
{
    World w;

    Obj_File obj("obj/cup-high.obj");
    w.create_world();

    run(w);
    int initial_size_bricks = bricks.size();

    cout << bricks.size() << endl;
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
    /*
    for (int i = 0; i < bricks.size(); i++) {
        bricks[i].print();
    }
    */
    for (auto it = bricks.begin(); it != bricks.end(); it++) {
        it->printRaw();
    }
    for (auto it = bricks.begin(); it != bricks.end(); it++) {
        it->printCSG();
    }
    cout << initial_size_bricks << endl;
    cout << bricks.size() << endl;


    return 0;
}
