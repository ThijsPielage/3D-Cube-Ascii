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

Mesh buildUnitCube() {
    Mesh cube;

    cube.vertices = {
        {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0},
        {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1}
    };

    cube.faces = {
        {0,1,2}, {0,2,3}, {4,5,6}, {4,6,7},
        {0,1,5}, {0,5,4}, {2,3,7}, {2,7,6},
        {0,3,7}, {0,7,4}, {1,2,6}, {1,6,5}
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