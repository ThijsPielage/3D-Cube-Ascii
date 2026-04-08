#include "lighting.h"
#include <string>
#include <algorithm>

char brightnessToAscii(float brightness) {
    const string ASCII = ".,:;irsXA253hMHGS#9B&@";;
    int index = brightness * (ASCII.size() - 1);
    return ASCII[index];
}

float brightnessFromNormal(const Vector3D& fNormal, const Vector3D& lightDir) {
    Vector3D n = normalize(fNormal);
    Vector3D l = normalize(lightDir);

    float brightness = -dot(n, l);
    return std::max(0.0f, brightness);
}