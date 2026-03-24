#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include "raster.h"

using namespace std;

struct Point3D {
    float x, y, z;
};

struct Triangle3D {
    Point3D p1, p2, p3;
};

struct CubeMesh {
    Point3D vertices[8];
    int triangles[12][3];
};

CubeMesh buildUnitCube() {
    CubeMesh cube;

    // Assign Vertices
    cube.vertices[0] = {0,0,0};
    cube.vertices[1] = {1,0,0};
    cube.vertices[2] = {1,1,0};
    cube.vertices[3] = {0,1,0};
    cube.vertices[4] = {0,0,1};
    cube.vertices[5] = {1,0,1};
    cube.vertices[6] = {0,1,1};
    cube.vertices[7] = {1,1,1};
    
    // Assign triangle indices
    int t[12][3] = {
        {0,1,2}, {0,2,3},
        {4,5,6}, {4,6,7},
        {0,1,5}, {0,5,4},
        {2,3,7}, {2,7,6},
        {0,3,7}, {0,7,4},
        {1,2,6}, {1,6,5}
    };

    for (int i = 0; i < 12; i++) {
        cube.triangles[i][0] = t[i][0];
        cube.triangles[i][1] = t[i][1];
        cube.triangles[i][2] = t[i][2];
    }

    return cube;
}

GridPoint ortographicToGrid(Point3D p) {
    GridPoint gp = {int(round(p.x)), int(round(p.y))};\
    return gp;
}

int main() {
    GridPoint p1 = {2, 2};
    GridPoint p2 = {15, 2};
    GridPoint p3 = {8, 7};
    GridTriangle t = {p1, p2, p3};

    vector<string> frame = buildEmptyFrame(20, 10);

    drawTriangle(frame, t, '#');
    showFrame(frame);

    return 0;
}