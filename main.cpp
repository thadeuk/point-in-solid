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

/*
 * Return:
 * 0 outside
 * 1 inside
 * 2 undefined
 */
int cube_test(World &w, double x, double y, double z, double side_size) {
    int ret;
    int status = -1;

    for (int i = 0; i <= 1; i++) {
       for (int j = 0; j <= 1; j++) {
          for (int k = 0; k <= 1; k++) {
              Point p1(x+side_size*i, y+side_size*j, z + side_size*k);
              while ((ret = w.point_in_polygon(p1, w.get_random_point() )) == 1);
              if (ret == 0) {
                  if (status == -1 || status == 0) {
                    status = 0;
                  }
                  else {
                      return 2;
                  }
              }
              if (ret == 2) {
                  if (status == -1 || status == 1) {
                      status = 1;
                  }
                  else {
                      return 2;
                  }
              }
          }
       }
    } 
    return status;
}

void run(World &w)
{
    int point_numbers = 0;
    int outside = 0;
    int inside = 0;
    int undefined = 0;
    int ret;
    double side_size = 0.2;

    for (double x = 0; x < 1; x += side_size) {
        printf("Feedback, x update\n");
        for (double y = 0; y < 1; y += side_size) {
            for (double z = 0; z < 1; z += side_size) {
                ret = cube_test(w, x, y, z, side_size);
                if (ret == 0)
                    outside++;
                if (ret == 1)
                    inside++;
                if (ret == 2)
                    undefined++;
            }
        }
    }
    printf("Outside cubes = %d\nInside cubes = %d\nUndefined cubes = %d\n", outside, inside, undefined);
}


int
main()
{
    World w;

    Obj_File obj("obj/catoms.obj");
    //w.normalize_points(40); 
    w.create_world();

    run(w);

    return 0;
}
