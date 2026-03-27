#include "lighting.h"
#include <string>

char brightnessToAscii(float v) {
    const string ASCII = ".:-=+*#%@";
    int index = v * (ASCII.size() - 1);
    return ASCII[index];
}

float brightnessFromNormal(const Vector3D& fNormal, const Vector3D& lightDir) {
    float brightness = -dot(normalize(fNormal), normalize(lightDir));
    brightness = max(0.0f, brightness);
    return brightness;
}