#include <iostream>
#include <cstdio>
#include <limits>
#include "world.h"
#include "obj_file.h"

#define MAX_SIZE 9. 

using namespace std;

void
add_cube(World &w)
{
    // Face 1 (Front)
    Point p1(0, 0, 0);
    Point p2(0, MAX_SIZE, 0);
    Point p3(MAX_SIZE, 0, 0);
    Point p4(MAX_SIZE, MAX_SIZE, 0);
    w.add_triangle(p1, p2, p3);
    w.add_triangle(p3, p2, p4);

    // Face 2 (Back face)
    Point p5(0, 0, MAX_SIZE);
    Point p6(0, MAX_SIZE, MAX_SIZE);
    Point p7(MAX_SIZE, 0, MAX_SIZE);
    Point p8(MAX_SIZE, MAX_SIZE, MAX_SIZE);
    w.add_triangle(p5, p6, p7);
    w.add_triangle(p7, p6, p8);

    // Face 3 (left lateral)
    Point p9(0, 0, 0);
    Point p10(0, 0, MAX_SIZE);
    Point p11(0, MAX_SIZE, 0);
    Point p12(0, MAX_SIZE, MAX_SIZE);
    w.add_triangle(p9, p10, p11);
    w.add_triangle(p11, p10, p12);

    // Face 4 (right lateral)
    Point p13(MAX_SIZE, 0, 0);
    Point p14(MAX_SIZE, 0, MAX_SIZE);
    Point p15(MAX_SIZE, MAX_SIZE, 0);
    Point p16(MAX_SIZE, MAX_SIZE, MAX_SIZE);
    w.add_triangle(p13, p14, p15);
    w.add_triangle(p15, p14, p16);

    // Face 5 (Base)
    Point p17(0, 0, 0);
    Point p18(MAX_SIZE, 0, 0);
    Point p19(0, 0, MAX_SIZE);
    Point p20(MAX_SIZE, 0, MAX_SIZE);
    w.add_triangle(p17, p18, p19);
    w.add_triangle(p19, p18, p20);

    // Face 6 (Top)
    Point p21(0, MAX_SIZE, 0);
    Point p22(MAX_SIZE, MAX_SIZE, 0);
    Point p23(0, MAX_SIZE, MAX_SIZE);
    Point p24(MAX_SIZE, MAX_SIZE, MAX_SIZE);
    w.add_triangle(p21, p22, p23);
    w.add_triangle(p23, p22, p24);
}

void
add_concave_form(World &w)
{
    // Face 1 (Front)
    Point p1(0, 0, 0);
    Point p2(0, MAX_SIZE, 0);
    Point p3(MAX_SIZE, 0, 0);
    Point p4(MAX_SIZE, MAX_SIZE, 0);
    Point new_p1(MAX_SIZE/2, 0, MAX_SIZE/2);
    Point new_p2(MAX_SIZE/2, MAX_SIZE, MAX_SIZE/2);
    w.add_triangle(p1, new_p1, new_p2);
    w.add_triangle(p1, p2, new_p2);
    w.add_triangle(p3, new_p1, new_p2);
    w.add_triangle(p3, p4, new_p2);

    // Face 2 (Back face)
    Point p5(0, 0, MAX_SIZE);
    Point p6(0, MAX_SIZE, MAX_SIZE);
    Point p7(MAX_SIZE, 0, MAX_SIZE);
    Point p8(MAX_SIZE, MAX_SIZE, MAX_SIZE);
    w.add_triangle(p5, p6, p7);
    w.add_triangle(p7, p6, p8);

    // Face 3 (left lateral)
    Point p9(0, 0, 0);
    Point p10(0, 0, MAX_SIZE);
    Point p11(0, MAX_SIZE, 0);
    Point p12(0, MAX_SIZE, MAX_SIZE);
    w.add_triangle(p9, p10, p11);
    w.add_triangle(p11, p10, p12);

    // Face 4 (right lateral)
    Point p13(MAX_SIZE, 0, 0);
    Point p14(MAX_SIZE, 0, MAX_SIZE);
    Point p15(MAX_SIZE, MAX_SIZE, 0);
    Point p16(MAX_SIZE, MAX_SIZE, MAX_SIZE);
    w.add_triangle(p13, p14, p15);
    w.add_triangle(p15, p14, p16);

    // Face 5 (Base)
    Point p17(0, 0, 0);
    Point p18(MAX_SIZE, 0, 0);
    Point p19(0, 0, MAX_SIZE);
    Point p20(MAX_SIZE, 0, MAX_SIZE);
    Point new_p3(MAX_SIZE/2, 0, MAX_SIZE/2);
    w.add_triangle(p17, p19, new_p3);
    w.add_triangle(p19, p20, new_p3);
    w.add_triangle(p18, p20, new_p3);

    // Face 6 (Top)
    Point p21(0, MAX_SIZE, 0);
    Point p22(MAX_SIZE, MAX_SIZE, 0);
    Point p23(0, MAX_SIZE, MAX_SIZE);
    Point p24(MAX_SIZE, MAX_SIZE, MAX_SIZE);
    Point new_p4(MAX_SIZE/2, MAX_SIZE, MAX_SIZE/2);
    w.add_triangle(p21, p23, new_p4);
    w.add_triangle(p23, p24, new_p4);
    w.add_triangle(p24, p22, new_p4);

}

void print_xml(World &w)
{
    int point_numbers = 0;
    int repeateds = 0;
    int ret;
    Point v1(1, 0, 0);
    Point v2(0, 1, 0);
    Point v3(0, 0, 1);

    for (int x = w.grid_min[0]; x <= w.grid_max[0]; x++) {
        for (int y = w.grid_min[1]; y <= w.grid_max[1]; y++) {
            for (int z = w.grid_min[2]; z <= w.grid_max[2]; z++) {
                Point p1(x,y,z);
                while ((ret = w.point_in_polygon(p1, w.get_random_point() )) == 1) repeateds++;
                if (ret == 2) {
                    point_numbers++;
                    printf("<block position=\"%d,%d,%d\" color=\"255,64,255\"/>\n",x, y, z); 
                }
            }
        }
    }
    printf("count = %d\n", point_numbers);
    printf("repeateds = %d\n", repeateds);
}


int
main()
{
    World w;

    //add_cube(w);
    //add_concave_form(w);
    //Obj_File obj("obj/diamond.obj");
    //Obj_File obj("obj/humanoid_tri.obj");
    //Obj_File obj("obj/cup2.obj");
    Obj_File obj("obj/example005.obj");
    w.normalize_points(40); 
    w.create_world();
    print_xml(w);
    /*
    Point p0(0,0,0);
    Point p1(0,1,0);
    Point x(1E-15, 1E-15, 1E-15);
    w.add_triangle(Point(0,0,0), Point(0,1,0), Point (1,1,0));
    cout << "in border ? " << w.triangles[0].is_in_border(x) << endl;
    cout << "contains point ? " << w.triangles[0].contains_point(Point(0+1E-15,1E-15,1E-11)) << endl;
    cout << "ray_intersect ? " << w.triangles[0].ray_intersect(Point(0+1E-15,1E-10,-0.0001), Point(1, 1, 1)) << endl;
    */
    //cout << w.triangles[0].is_between_points(x, p0, p1) << endl;

    return 0;
}
