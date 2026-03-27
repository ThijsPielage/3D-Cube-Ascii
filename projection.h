#pragma once

#include "Vector3D.h"
#include "geometry.h"
#include "raster.h"
#include "lighting.h"

struct FaceDepth {
    int index;
    float depth;
};

using DepthMap = vector<FaceDepth>;
using FaceIndices = vector<int>;

FaceIndices backFaceCull(const Mesh& mesh, const Vector3D& cameraDir);
GridPoint orthographicToGrid(const Frame& frame, const Vector3D& p, const Vector3D& cameraDir);
void projectMesh(Frame& frame, const Mesh& mesh, const Vector3D& cameraDir, const Vector3D& lightDir);