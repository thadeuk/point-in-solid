#include <iostream>
#include "geometrics.h"

using namespace std;

class Shape3D
{
    virtual bool isInside(Point initial_p, Point p) = 0;
};

class Cube : public Shape3D
{
public:
    double size_x;
    double size_y;
    double size_z;
    bool center;

    Cube (double _size_x, double _size_y, double _size_z) : size_x(_size_x), size_y(_size_y), size_z(_size_z), center(false){};

    Cube (double _size_x, double _size_y, double _size_z, bool _center) : size_x(_size_x), size_y(_size_y), size_z(_size_z), center(_center){};

    void print() {
        cout << "CUBE " << size_x << ' ' << size_y << ' ' << size_z << endl;
    }

    bool isInside(Point initial_p, Point p) {
        if (center) {
            if (fabs(p.x - initial_p.x) < size_x/2 && fabs(p.y - initial_p.y) < size_y/2 && fabs(p.z - initial_p.z) < size_z/2)
                return true;
        }
        else {
            if ((p.x - initial_p.x) < size_x && (p.y - initial_p.y) < size_y && (p.z - initial_p.z) < size_z)
                return true;
        }
        return false;
    }
};

class BoolOperator
{
public:
    enum class bool_operator_t {bool_union, bool_difference, bool_intersection};
    bool_operator_t my_type;

    BoolOperator(bool_operator_t bool_type) : my_type(bool_type) {};

    void print() {
        switch(my_type) {
            case bool_operator_t::bool_union:
                cout << "UNION" << endl;
                break;
            case bool_operator_t::bool_difference:
                cout << "DIFFERENCE" << endl;
                break;
            case bool_operator_t::bool_intersection:
                cout << "INTERSECTION" << endl;
        }
    }
};
