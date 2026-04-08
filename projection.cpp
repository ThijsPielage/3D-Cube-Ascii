#include "projection.h"
#include <cmath>
#include <algorithm>

FaceIndices backFaceCull(const Mesh& mesh, const Vector3D& cameraDir) {
    FaceIndices visible;

    for (int i = 0; i < (int)mesh.faces.size(); i++) {
        const auto& face = mesh.faces[i];

        const Vector3D& a = mesh.vertices[face[0]];
        const Vector3D& b = mesh.vertices[face[1]];
        const Vector3D& c = mesh.vertices[face[2]];

        if (dot(getFaceNormal(a, b, c), cameraDir) > 0) {
            visible.push_back(i);
        }
    }

    return visible;
}

GridPoint orthographicToGrid(const Frame& frame, const Vector3D& p, const Vector3D& cameraDir) {
    Vector3D forward = normalize(cameraDir);
    Vector3D temp = {0, 1, 0};
    if (fabs(dot(temp, forward)) > 0.99) temp = {1, 0, 0}; // avoid parallel
    Vector3D right = normalize(cross(temp, forward));
    Vector3D up = cross(forward, right);

    float px = dot(p, right);
    float py = dot(p, up);

    int cx = frame[0].size() / 2;
    int cy = frame.size() / 2;
    GridPoint gp = { int(round(px * 2)) + cx, int(round(py)) + cy };
    return gp;
}

GridPoint perspectiveToGrid(const Frame& frame, const Vector3D& p, const Vector3D& cameraDir) {
    Vector3D forward = normalize(cameraDir);
    Vector3D temp = {0, 1, 0};
    if (fabs(dot(temp, forward)) > 0.99) temp = {1, 0, 0}; // avoid parallel
    Vector3D right = normalize(cross(temp, forward));
    Vector3D up = cross(forward, right);

    float px = dot(p, right);
    float py = dot(p, up);
    float pz = dot(p, forward);

    px /= pz;
    py /= pz;

    int cx = frame[0].size() / 2;
    int cy = frame.size() / 2;
    GridPoint gp = { int(round(px * 2)) + cx, int(round(py)) + cy };
    return gp;
}

void projectMesh(Frame& frame, DepthBuffer& db, const Mesh& mesh,
                 const Vector3D& cameraDir, const Vector3D& lightDir)
{
    auto visible = backFaceCull(mesh, cameraDir);

    Vector3D cam = normalize(cameraDir);

    for (const auto& faceIndex : visible) {
        const auto& face = mesh.faces[faceIndex];

        Vector3D a = mesh.vertices[face[0]];
        Vector3D b = mesh.vertices[face[1]];
        Vector3D c = mesh.vertices[face[2]];

        Vector3D normal = getFaceNormal(a, b, c);
        float brightness = brightnessFromNormal(normal, lightDir);
        const char shade = brightnessToAscii(brightness);

        GridPoint gp1 = orthographicToGrid(frame, a, cameraDir);
        GridPoint gp2 = orthographicToGrid(frame, b, cameraDir);
        GridPoint gp3 = orthographicToGrid(frame, c, cameraDir);

        GridTriangle t = {gp1, gp2, gp3};

        // Pass vertices too so we can compute depth
        drawTriangle(frame, db, t, a, b, c, cam, shade);
    }
}