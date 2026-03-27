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
    Mesh cube = buildCube(20);

    Vector3D Raxis = {1, 1, 2};
    Vector3D cameraDir = {0, 0, -1};
    Vector3D lightDir = {1, 1, -1};
    float dtheta = 0.05;

    while (1) {
        clearScreen();
        Frame frame = buildEmptySquareFrame(50);
        rotateMesh(cube, Raxis, dtheta);
        projectMesh(frame, cube, cameraDir, lightDir);
        showFrame(frame);
        this_thread::sleep_for(chrono::milliseconds(20));
    }

    return 0;
}