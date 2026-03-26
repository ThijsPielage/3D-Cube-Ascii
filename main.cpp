#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include "raster.h"
#include "Vector3D.h"

using namespace std;

struct CubeMesh {
    vector<Vector3D> vertices;
    vector<vector<int>> faces;
};

void transposeCube(CubeMesh& cube, const Vector3D& b) {
    for (auto& v : cube.vertices) {
        transposeVector3D(v, b);
    }
}

void scaleCube(CubeMesh& cube, const Vector3D& b) {
    for (auto& v : cube.vertices) {
        scaleVector3D(v, b);
    }
}

CubeMesh buildUnitCube() {
    CubeMesh cube;

    cube.vertices = {
        {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0},
        {0,0,1}, {1,0,1}, {0,1,1}, {1,1,1}
    };

    cube.faces = {
        {0,1,2}, {0,2,3}, {4,5,6}, {4,6,7},
        {0,1,5}, {0,5,4}, {2,3,7}, {2,7,6},
        {0,3,7}, {0,7,4}, {1,2,6}, {1,6,5}
    };

    return cube;
}

GridPoint orthographicToGrid(Vector3D p) {
    GridPoint gp = {int(round(p.x * 2)), int(round(p.y))};\
    return gp;
}



void projectCube(Frame& frame, const CubeMesh& cube) {
    for (const auto& face : cube.faces) {
        GridPoint gp1 = orthographicToGrid(cube.vertices[face[0]]);
        GridPoint gp2 = orthographicToGrid(cube.vertices[face[1]]);
        GridPoint gp3 = orthographicToGrid(cube.vertices[face[2]]);

        GridTriangle t = {gp1, gp2, gp3};
        drawTriangle(frame, t, '#');
    }
}

int main() {
    CubeMesh cube = buildUnitCube();
    Vector3D scale = {5, 5, 5};
    scaleCube(cube, scale);
    Vector3D shift = {2, 2, 2};
    transposeCube(cube, shift);

    Frame frame = buildEmptyFrame(20, 10);
    projectCube(frame, cube);

    showFrame(frame);

    return 0;
}