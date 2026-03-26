#pragma once
#include "Vector3D.h"

struct Mesh {
    vector<Vector3D> vertices;
    vector<vector<int>> faces;
};

Mesh buildUnitCube();
Mesh buildCube(const float x, const float y, const float z);
Mesh buildCube(const float s);

void transposeMesh(Mesh& mesh, const Vector3D& b);

void scaleMesh(Mesh& mesh, const Vector3D& b);
void scalemesh(Mesh& mesh, float b);

void rotateMesh(Mesh& mesh, Vector3D axis, float angle);

Vector3D findMeshCenter(const Mesh& mesh);
void centerMesh(Mesh& mesh);