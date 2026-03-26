#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include <chrono>
#include <thread>

#include "raster.h"
#include "Vector3D.h"
#include "geometry.h"

using namespace std;

GridPoint orthographicToGrid(Frame& frame, Vector3D p) {
    int cx = frame[0].size() / 2;
    int cy = frame.size() / 2;
    GridPoint gp = {int(round(p.x * 2)) + cx, int(round(p.y)) + cy};
    return gp;
}

void projectMesh(Frame& frame, const Mesh& mesh) {
    for (const auto& face : mesh.faces) {
        GridPoint gp1 = orthographicToGrid(frame, mesh.vertices[face[0]]);
        GridPoint gp2 = orthographicToGrid(frame, mesh.vertices[face[1]]);
        GridPoint gp3 = orthographicToGrid(frame, mesh.vertices[face[2]]);

        GridTriangle t = {gp1, gp2, gp3};
        drawTriangle(frame, t, '#');
    }
}

int main() {
    Mesh cube = buildCube(10);

    Vector3D axis = {1, 1, 2};
    float dtheta = 0.1;
    while (1) {
        clearScreen();
        Frame frame = buildEmptySquareFrame(20);
        rotateMesh(cube, axis, dtheta);
        projectMesh(frame, cube);
        showFrame(frame);
        this_thread::sleep_for(chrono::milliseconds(50));
    }

    return 0;
}