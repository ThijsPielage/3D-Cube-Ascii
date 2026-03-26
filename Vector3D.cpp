#include "Vector3D.h"

void transposeVector3D(Vector3D& a, const Vector3D& b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
}

void transposeVector3D(Vector3D& a, float x, float y, float z) {
    Vector3D b = {x, y, z};
    transposeVector3D(a, b);
}

void scaleVector3D(Vector3D& a, const Vector3D& b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
}

void scaleVector3D(Vector3D& a, float x, float y, float z) {
    Vector3D b = {x, y, z};
    scaleVector3D(a, b);
}

void scaleVector3D(Vector3D& a, float s) {
    Vector3D b = {s, s, s};
    scaleVector3D(a, b);
}