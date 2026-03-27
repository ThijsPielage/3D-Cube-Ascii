#include "geometry.h"

void transposeMesh(Mesh& mesh, const Vector3D& b) {
    for (auto& v : mesh.vertices) {
        transposeVector3D(v, b);
    }
}

void scaleMesh(Mesh& mesh, const Vector3D& b) {
    for (auto& v : mesh.vertices) {
        scaleVector3D(v, b);
    }
}

void scaleMesh(Mesh& mesh, float b) {
    for (auto& v : mesh.vertices) {
        scaleVector3D(v, b);
    }
}

void rotateMesh(Mesh& mesh, Vector3D axis, float angle) {
    for (auto& v : mesh.vertices) {
        rotateVector3D(v, axis, angle);
    }
}

Vector3D findMeshCenter(const Mesh& mesh) {
    Vector3D center = {0,0,0};

    for (const auto& v : mesh.vertices) {
        center.x += v.x;
        center.y += v.y;
        center.z += v.z;
    }

    float n = mesh.vertices.size();

    center.x /= n;
    center.y /= n;
    center.z /= n;

    return center;
}

void centerMesh(Mesh& mesh) {
    Vector3D center = findMeshCenter(mesh);

    Vector3D negCenter = {-center.x, -center.y, -center.z};

    transposeMesh(mesh, negCenter);
}

Vector3D getFaceNormal(const Vector3D& a, const Vector3D& b, const Vector3D& c) {
        Vector3D ab = subVector3D(b , a);
        Vector3D ac = subVector3D(c, a);
        return cross(ab, ac);
}

/* ########### PRIMITIVES #################*/

Mesh buildUnitCube() {
    Mesh cube;

    cube.vertices = {
        {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0},
        {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1}
    };

    cube.faces = {
        {0,1,2}, {0,2,3},
        {4,6,5}, {4,7,6},
        {0,3,7}, {0,7,4},
        {1,5,6}, {1,6,2},
        {0,4,5}, {0,5,1},
        {3,2,6}, {3,6,7}
    };

    centerMesh(cube);

    return cube;
}

Mesh buildCube(const float x, const float y, const float z) {
    Mesh cube = buildUnitCube();
    Vector3D scalars = {x, y, z};
    scaleMesh(cube, scalars);
    return cube;
}

Mesh buildCube(const float s) {
    Mesh cube = buildUnitCube();
    Vector3D scalars = {s, s, s};
    scaleMesh(cube, scalars);
    return cube;
}



Mesh buildUnitPyramid() {
    Mesh pyrm;

    pyrm.vertices = {
        {0, 0, 0}, {1, 0, 0}, {1, 1, 0},
        {0, 1, 0}, {0.5, 0.5, 1}
    };

    pyrm.faces = {
    {0,1,2}, {0,2,3},
    {0,4,1},
    {1,4,2},
    {2,4,3},
    {3,4,0}
};

    centerMesh(pyrm);

    return pyrm;
}

Mesh buildPyramid(const float x, const float y, const float z) {
    Mesh pyrm = buildUnitPyramid();
    Vector3D scalars = {x, y, z};
    scaleMesh(pyrm, scalars);
    return pyrm;
}

Mesh buildPyramid(const float s) {
    Mesh pyrm = buildUnitPyramid();
    Vector3D scalars = {s, s, s};
    scaleMesh(pyrm, scalars);
    return pyrm;
}
