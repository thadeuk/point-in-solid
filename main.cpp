#include <iostream>
#include <cstdio>
#include <limits>
#include <algorithm>
#include <fstream>
#include <thread>
#include <atomic>
#include <omp.h>
#include "world.h"
#include "obj_file.h"
#include "stoy.h"
#define EPSILON 1E-5

using namespace std;

const float M_SQRT2_2 = M_SQRT2/2;

void print_mesh_xml(World &w, Point p, int x, int y, int z)
{
    int ret;
    while ((ret = w.point_in_polygon(p, w.get_random_point() )) == 1);
    if (ret == 2) {
        printf("<block position=\"%d,%d,%d\" color=\"0,0,255\"/>\n",x,y,z); 
    }
}

void print_xml(World &w, BrickList &blist)
{
    int point_numbers = 0;
    int repeateds = 0;
    int ret;
    Point p1;
    /*
    w.grid_min[0] = -10;
    w.grid_min[1] = -10;
    w.grid_min[2] = -10;
    w.grid_max[0] = 10;
    w.grid_max[1] = 10;
    w.grid_max[2] = 10;
    */ 

    int areaX = w.grid_max[0] - w.grid_min[0];
    int areaY = w.grid_max[1] - w.grid_min[1];
    int areaZ = ceil(M_SQRT2*(w.grid_max[2] - w.grid_min[2]));

    cout << "<?xml version=\"1.0\" standalone=\"no\" ?>"<< endl;
    cout << "<world gridSize=\"200,200,200\" windowSize=\"1800,900\" maxSimulationTime=\"5 mn\">" << endl;
  	cout << "<camera target=\"200,200,200\" directionSpherical=\"0,38," << 2000 << "\" angle=\"50\" far=\"" << 2000*2 << "\"/>" << endl;
  	cout << "<spotlight target=\"200,200,200\" directionSpherical=\"-30,50,2000\" angle=\"45\"/>" << endl;
  	cout << "<blockList color=\"128,128,128\" blocksize=\"10.0,10.0,10.0\">" << endl;
    

    for (int z = 0; z <= areaZ; z++) {
        p1.z = w.grid_min[2] + 0.5 + z*M_SQRT2_2;
        for (int y = 0; y <= areaY; y++) {
            for (int x = 0; x <= areaX; x++) {
                if (z%2) {
                    p1.x = w.grid_min[0]+x+1.0;
                    p1.y = w.grid_min[1]+y+1.0;
                }
                else {
                    p1.x = w.grid_min[0]+x+0.5;
                    p1.y = w.grid_min[1]+y+0.5;
                }
                //print_mesh_xml(w, p1, x, y, z);        
                if (blist.isInside(p1))
                    printf("<block position=\"%d,%d,%d\" color=\"0,0,255\"/>\n",x,y,z); 
            }
        }
    }
    /*
    int x = 31;
    int y = 80;
    int z = 81;
    p1.z = w.grid_min[2] + 0.5 + z*M_SQRT2_2;
    if (z%2) {
        p1.x = w.grid_min[0]+x+1.0;
        p1.y = w.grid_min[1]+y+1.0;
    }
    else {
        p1.x = w.grid_min[0]+x+0.5;
        p1.y = w.grid_min[1]+y+0.5;
    }
    p1.x = -16;
    p1.y = -4.97635;
    p1.z = 40.0256;
    p1.print();
    print_mesh_xml(w, p1, x, y, z);        
    */
    cout << "</blockList>" << endl;
    cout << "</world>" << endl;
}

int
main()
{
    World w;

    Obj_File obj("obj/voiture-highresolution_fixed.obj");
    w.create_world();

    w.grid_min[0] = (int)w.grid_min[0];
    w.grid_min[1] = (int)w.grid_min[1];
    w.grid_min[2] = (int)w.grid_min[2];

    BrickList blist;
//    blist.createList(w, 5);
//    blist.joinBricks();
//    blist.printCSG();
    blist.readBrickFromCSG("voiture-stoy3.csg");
    print_xml(w,blist);

    return 0;
}
