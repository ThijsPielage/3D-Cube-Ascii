#include "Vector3D.h"
#include <cmath>

float dot(const Vector3D& a, const Vector3D& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vector3D cross(const Vector3D& a, const Vector3D& b) {
    return {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
}

Vector3D addVector3D(const Vector3D& a, const Vector3D& b) {
    return {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

Vector3D subVector3D(const Vector3D& a, const Vector3D& b) {
    return {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}

Vector3D normalize(const Vector3D& v) {
    float len = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    return {v.x/len, v.y/len, v.z/len};
}

Vector3D scalarMult(Vector3D& v, const float s) {
    Vector3D scaledVector = {
        v.x * s,
        v.y * s,
        v.z * s
    };
    return scaledVector;
}

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

void rotateVector3D(Vector3D& v, const Vector3D& axis, float theta) {
    Vector3D u = normalize(axis);

    float cosT = cos(theta);
    float sinT = sin(theta);

    Vector3D term1 = scalarMult(v, cosT);

    Vector3D cr = cross(u, v);
    Vector3D term2 = scalarMult(cr, sinT);

    float dotAV = dot(u, v);
    Vector3D term3 = scalarMult(u, dotAV * (1 - cosT));

    v = addVector3D(term1, addVector3D(term2, term3));
}