#pragma once

#include "Vector3D.h"

char brightnessToAscii(float v);
float brightnessFromNormal(const Vector3D& fNormal, const Vector3D& lightDir);