#pragma once
#include <vector>

using namespace std;

struct Vector3D {
    float x, y, z;
};

float dot(const Vector3D& a, const Vector3D& b);
Vector3D cross(const Vector3D& a, const Vector3D& b);
Vector3D addVector3D(const Vector3D& a, const Vector3D& b);
Vector3D subVector3D(const Vector3D& a, const Vector3D& b);
Vector3D normalize(const Vector3D& v);
Vector3D scalarMult(Vector3D& v, const float s);

void transposeVector3D(Vector3D& a, const Vector3D& b);
void transposeVector3D(Vector3D& a, float x, float y, float z);

void scaleVector3D(Vector3D& a, const Vector3D& b);
void scaleVector3D(Vector3D& a, float x, float y, float z);
void scaleVector3D(Vector3D& a, float s);

void rotateVector3D(Vector3D& v, const Vector3D& axis, float theta);