#pragma once
#include <vector>

using namespace std;

struct Vector3D {
    float x, y, z;
};

void transposeVector3D(Vector3D& a, const Vector3D& b);
void transposeVector3D(Vector3D& a, float x, float y, float z);

void scaleVector3D(Vector3D& a, const Vector3D& b);
void scaleVector3D(Vector3D& a, float x, float y, float z);
void scaleVector3D(Vector3D& a, float s);