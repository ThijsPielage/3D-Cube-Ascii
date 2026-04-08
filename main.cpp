#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include <chrono>
#include <thread>

#include "raster.h"
#include "Vector3D.h"
#include "geometry.h"
#include "projection.h"

using namespace std;

int main() {
    Mesh cube = buildCube(15);
    transposeMesh(cube, {20, 20, 20});
    Mesh sphere = buildUVSphere(10, 10, 20);

    Vector3D Raxis = {1, 1, 2};
    Vector3D cameraDir = {0, 0, -1};
    Vector3D lightDir = {-1, -1, 1};
    float dtheta = 0.05;

    while (1) {
        clearScreen();
        Frame frame = buildEmptySquareFrame(50);
        DepthBuffer db = initializeDepthBuffer(frame);
        rotateMesh(cube, Raxis, dtheta);
        rotateMesh(sphere, Raxis, dtheta);
        projectMesh(frame, db,  cube, cameraDir, lightDir);
        projectMesh(frame, db,  sphere, cameraDir, lightDir);
        showFrame(frame);
        this_thread::sleep_for(chrono::milliseconds(20));
    }

    return 0;
}