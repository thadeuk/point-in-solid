#include <iostream>
#include <cstdio>
#include <limits>
#include <algorithm>
#include <fstream>
#include <thread>
#include <atomic>
#include "world.h"
#include "obj_file.h"
#define EPSILON 1E-5

using namespace std;

atomic<int> small_outside(0);
atomic<int> small_inside(0);
atomic<int> small_undefined(0);
vector<thread> threads;

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

bool IsLess(double a, double b)
{
    return b - a > EPSILON;
}

bool AreEqual(double a, double b)
{
    return fabs(a - b) < EPSILON;
}

void run_small(World &w, double side_size_big, double initial_point_x, double initial_point_y, double initial_point_z)
{
    int ret;
    double side_size = 0.0025;

    for (double x = initial_point_x; IsLess(x, initial_point_x+side_size_big); x += side_size) {
        for (double y = initial_point_y; IsLess(y, initial_point_y + side_size_big); y += side_size) {
            for (double z = initial_point_z; IsLess(z, initial_point_z + side_size_big); z += side_size) {
                ret = cube_test(w, x, y, z, side_size);
                if (ret == 0) {
                    small_outside++;
                }
                if (ret == 1) {
                    small_inside++;
                }
                if (ret == 2) {
                    small_undefined++;
                }
            }
        }
    }
}

void run(World &w)
{
    int outside = 0;
    int inside = 0;
    int undefined = 0;


    int ret;
    double side_size = 0.005;
    double initial_point = -0.5;
    double end_point = 0.5;
    int t = 0;

    for (double x = initial_point; IsLess(x, end_point); x += side_size) {
        printf("Feedback, x update. x = %lf\n", x);
        if (threads.size() - t > 100) {
            for (; t < threads.size(); t++) {
                threads[t].join();
            }
        }
        for (double y = initial_point; IsLess(y, end_point); y += side_size) {
            for (double z = initial_point; IsLess(z, end_point); z += side_size) {
                ret = cube_test(w, x, y, z, side_size);
                if (ret == 0)
                    outside++;
                if (ret == 1) {
                    inside++;
                }
                if (ret == 2) {
                    undefined++;
                    threads.push_back(thread(run_small, ref(w), side_size, x, y, z));
                    //run_small(w, side_size, x, y, z);
                }
            }
        }
    }
    printf("Waiting...\n");
    for (; t < threads.size(); t++) {
        threads[t].join();
    }

    //for_each(threads.begin(), threads.end(),
    //                                std::mem_fn(&thread::join));
    printf("Inside cubes = %d\nOutside cubes = %d\nUndefined cubes = %d\n", inside, outside, undefined);
    printf("Small inside cubes = %d\nSmall outside cubes = %d\nSmall undefined cubes = %d\n", small_inside.load(memory_order_relaxed), small_outside.load(memory_order_relaxed), small_undefined.load(memory_order_relaxed));
}

int
main()
{
    World w;

    Obj_File obj("obj/catoms.obj");
    w.create_world();

    run(w);

    return 0;
}
