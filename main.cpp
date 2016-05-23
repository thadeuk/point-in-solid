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
#define EPSILON 1E-5

using namespace std;

const float M_SQRT2_2 = M_SQRT2*.5;

void print_xml(World &w)
{
    int point_numbers = 0;
    int repeateds = 0;
    int ret;
    Point p1;
    
    cout << "<?xml version=\"1.0\" standalone=\"no\" ?>"<< endl;
    cout << "<world gridSize=\"200,200,200\" windowSize=\"1800,900\" maxSimulationTime=\"5 mn\">" << endl;
  	cout << "<camera target=\"200,200,200\" directionSpherical=\"0,38," << 2000 << "\" angle=\"50\" far=\"" << 2000*2 << "\"/>" << endl;
  	cout << "<spotlight target=\"200,200,200\" directionSpherical=\"-30,50,2000\" angle=\"45\"/>" << endl;
  	cout << "<blockList color=\"128,128,128\" blocksize=\"10.0,10.0,10.0\">" << endl;
    
    int areaX = w.grid_max[0] - w.grid_min[0];
    int areaY = w.grid_max[1] - w.grid_min[1];
    int areaZ = w.grid_max[2] - w.grid_min[2];

    for (int z = 0; z <= areaZ; z++) {
        for (int y = 0; y <= areaY; y++) {
            for (int x = 0; x <= areaX; x++) {

                p1.z = w.grid_min[2] + 0.5 + z*M_SQRT2_2;
                if (z%2) {
                    p1.x = w.grid_min[0]+x+1.0;
                    p1.y = w.grid_min[1]+y+1.0;
                }
                else {
                    p1.x = w.grid_min[0]+x+0.5;
                    p1.y = w.grid_min[1]+y+0.5;
                }
                
                while ((ret = w.point_in_polygon(p1, w.get_random_point() )) == 1) repeateds++;
                if (ret == 2) {
                    point_numbers++;
                    printf("<block position=\"%d,%d,%d\" color=\"0,0,255\"/>\n",x,y,z); 
                }
            }
        }
    }
    cout << "</blockList>" << endl;
    cout << "</world>" << endl;
}

int
main()
{
    World w;

    Obj_File obj("obj/voiture-highresolution_fixed.obj");
    w.create_world();

    print_xml(w);

    return 0;
}
