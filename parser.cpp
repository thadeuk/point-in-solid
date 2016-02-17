#include <iostream>
#include <vector>
#include "shape3d.h"

using namespace std;


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

        Node cube11(node_t::shape);
        cube11.value = new Cube(30, 30, 30, true);

        Node sphere1(node_t::shape);
        sphere1.value = new Sphere(20);

        root.add_child(cube11);
        root.add_child(sphere1);
        /*root.add_child(c1);
        c1.add_child(cube1);
        c1.add_child(cube2);
        c1.add_child(cube3);
        c1.add_child(cube4);
        root.add_child(c2);
        c2.add_child(cube5);
        c2.add_child(cube6);
        c2.add_child(cube7);
        */

        root.print_tree();
    }

    bool check_point(Node *n, Point initial_point, Point p) {
        if (n->type == node_t::shape) {
            Shape3D *shape = static_cast<Shape3D *>(n->value);
            return shape->isInside(initial_point, p);
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
            }

            return false;
        }
    }

};

int
main()
{

    Parse p("oi");


}
