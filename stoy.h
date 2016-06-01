#pragma once
#include <iostream>
#include <cmath>
#include <list>
#define EPSILON 1E-5

using namespace std;


class Brick
{
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
        return a < b ? a : b;
    }

    double greaterd(double a, double b)
    {
        return a > b ? a : b;
    }

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

    bool isInside(Point &p) {
        if (p.x >= lowerx && p.y >= lowery && p.z >= lowerz
                && p.x <= upperx && p.y <= uppery && p.z <= upperz) {
            return true;
        }
        return false;
    }
};


class BrickList
{

private:
    list<Brick> bricks;

public:
    void readBrickFromCSG(string path);
    void createList(World &w, double side_size);
    void joinBricks();
    bool isInside(Point &p);
    void printCSG();
    void print();
};
