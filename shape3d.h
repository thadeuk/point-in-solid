#include <iostream>
#include <vector>
#include "geometrics.h"

using namespace std;

class Shape3D
{
public:
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

class Sphere : public Shape3D
{
public:
    double radius;
    Sphere (double _radius) : radius(_radius){};

    void print() {
        cout << "SPHERE " << radius << endl;
    }

    bool isInside(Point initial_p, Point p) {
    //    double dist = sqrt(pow(p.x-initial_p.x, 2) + pow(p.y-initial_p.y, 2) + pow(p.z-initial_p.z, 2));
        double dist = 40;
        if (dist < radius)
            return true;
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

enum class node_t {bool_op, shape};

class Node
{
public:
    node_t type;
    void *value;
    vector<Node *> vchildren;

    Node() {};
    Node(node_t _type) : type(_type) {};
    void add_child(Node &n) {
        vchildren.push_back(&n);
    }

    void print_tree() {
        switch(type) {
            case node_t::bool_op:
                cout << "bool operator!" << endl;
                break;
            case node_t::shape:
                cout << "shape!" << endl;
                break;
        }

        cout << "children = " << vchildren.size() << endl;
        for (int i = 0; i < vchildren.size(); i++) {
            vchildren[i]->print_tree();
        }

    }
};
