#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include <chrono>
#include <thread>

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

void scaleCube(CubeMesh& cube, float b) {
    for (auto& v : cube.vertices) {
        scaleVector3D(v, b);
    }
}

void rotateCube(CubeMesh& cube, Vector3D axis, float angle) {
    for (auto& v : cube.vertices) {
        rotateVector3D(v, axis, angle);
    }
}

CubeMesh buildUnitCube() {
    CubeMesh cube;

    cube.vertices = {
        {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0},
        {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1}
    };

    cube.faces = {
        {0,1,2}, {0,2,3}, {4,5,6}, {4,6,7},
        {0,1,5}, {0,5,4}, {2,3,7}, {2,7,6},
        {0,3,7}, {0,7,4}, {1,2,6}, {1,6,5}
    };

    return cube;
}

Vector3D findCubeCenter(const CubeMesh& cube) {
    Vector3D center = {0,0,0};

    for (const auto& v : cube.vertices) {
        center.x += v.x;
        center.y += v.y;
        center.z += v.z;
    }

    float n = cube.vertices.size();

    center.x /= n;
    center.y /= n;
    center.z /= n;

    return center;
}

void centerCube(CubeMesh& cube) {
    Vector3D center = findCubeCenter(cube);

    Vector3D negCenter = {-center.x, -center.y, -center.z};

    transposeCube(cube, negCenter);
}

GridPoint orthographicToGrid(Frame& frame, Vector3D p) {
    int cx = frame[0].size() / 2;
    int cy = frame.size() / 2;
    GridPoint gp = {int(round(p.x * 2)) + cx, int(round(p.y)) + cy};
    return gp;
}

void projectCube(Frame& frame, const CubeMesh& cube) {
    for (const auto& face : cube.faces) {
        GridPoint gp1 = orthographicToGrid(frame, cube.vertices[face[0]]);
        GridPoint gp2 = orthographicToGrid(frame, cube.vertices[face[1]]);
        GridPoint gp3 = orthographicToGrid(frame, cube.vertices[face[2]]);

        GridTriangle t = {gp1, gp2, gp3};
        drawTriangle(frame, t, '#');
    }
}

int main() {
    CubeMesh cube = buildUnitCube();
    scaleCube(cube, 10);
    centerCube(cube);

    Vector3D axis = {1, 1, 2};
    float dtheta = 0.1;
    while (1) {
        clearScreen();
        Frame frame = buildEmptySquareFrame(20);
        rotateCube(cube, axis, dtheta);
        projectCube(frame, cube);
        showFrame(frame);
        this_thread::sleep_for(chrono::milliseconds(50));
    }

    return 0;
}