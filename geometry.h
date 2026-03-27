#pragma once
#include "Vector3D.h"

using MeshVertices = vector<Vector3D>;
using MeshFaces = vector<vector<int>>;

struct Mesh {
    MeshVertices vertices;
    MeshFaces faces;
};

Mesh buildUnitCube();
Mesh buildCube(const float x, const float y, const float z);
Mesh buildCube(const float s);

Mesh buildUnitPyramid();
Mesh buildPyramid(const float x, const float y, const float z);
Mesh buildPyramid(const float s);

void transposeMesh(Mesh& mesh, const Vector3D& b);

void scaleMesh(Mesh& mesh, const Vector3D& b);
void scalemesh(Mesh& mesh, float b);

void rotateMesh(Mesh& mesh, Vector3D axis, float angle);

Vector3D findMeshCenter(const Mesh& mesh);
void centerMesh(Mesh& mesh);

Vector3D getFaceNormal(const Vector3D& p1, const Vector3D& p2, const Vector3D& p3);