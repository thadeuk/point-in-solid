#include <iostream>
#include <vector>
#include "shape3d.h"

using namespace std;

enum class node_t {group, bool_op, shape};

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

class Parse
{
public:
    string str;
    Node root;

    Parse (string s): str(s) {
        root.type = node_t::bool_op;
        root.value = new BoolOperator(BoolOperator::bool_operator_t::bool_difference);

        Node c1(node_t::bool_op);
        c1.value = new BoolOperator(BoolOperator::bool_operator_t::bool_union);

        Node cube1(node_t::shape);
        cube1.value = new Cube(15, 15, 15);
        Node cube2(node_t::shape);
        cube2.value = new Cube(20, 7.5, 7.5);
        Node cube3(node_t::shape);
        cube3.value = new Cube(7.5, 20, 7.5);
        Node cube4(node_t::shape);
        cube4.value = new Cube(7.5, 7.5, 20);

        Node c2(node_t::bool_op);
        c2.value = new BoolOperator(BoolOperator::bool_operator_t::bool_union);
        
        Node cube5(node_t::shape);
        cube5.value = new Cube(25, 5, 5);
        Node cube6(node_t::shape);
        cube6.value = new Cube(5, 25, 5);
        Node cube7(node_t::shape);
        cube7.value = new Cube(5, 5, 25);

        root.add_child(c1);
        c1.add_child(cube1);
        c1.add_child(cube2);
        c1.add_child(cube3);
        c1.add_child(cube4);
        root.add_child(c2);
        c2.add_child(cube5);
        c2.add_child(cube6);
        c2.add_child(cube7);

        root.print_tree();

        Point initial_point(0,0,0);
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {
                for (int k = 0; k < 30; k++) {
                    if (check_point(&root, initial_point, Point(i, j, k))) {
                       printf("<block position=\"%d,%d,%d\" color=\"255,64,255\"/>\n",i, j, k); 
                    }
                }
            }
        }
    }

    bool check_point(Node *n, Point initial_point, Point p) {
        if (n->type == node_t::shape) {
            Cube *c = static_cast<Cube *>(n->value);
            /*
            c->print();
            if (c->isInside(initial_point, p))
                cout << "is inside" << endl;
            else 
                cout << "not inside";
                */
            return c->isInside(initial_point, p);
        }
        if (n->type == node_t::bool_op) {
            BoolOperator* b_op = static_cast<BoolOperator *>(n->value);
            if (b_op->my_type == BoolOperator::bool_operator_t::bool_union) {
                for (int i = 0; i < n->vchildren.size(); i++) {
                    if (check_point(n->vchildren[i], initial_point, p))
                        return true;
                }
            }
            if (b_op->my_type == BoolOperator::bool_operator_t::bool_difference) {
                if (n->vchildren.size() > 1) {
                    if (check_point(n->vchildren[0], initial_point, p)) {
                        for (int i = 1; i < n->vchildren.size(); i++) {
                            if (check_point(n->vchildren[i], initial_point, p))
                                return false;
                        }
                        return true;
                    }
                }
                return false;
            }
        }
    }

};

int
main()
{

    Parse p("oi");


}

