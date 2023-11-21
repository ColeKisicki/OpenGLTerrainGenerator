#pragma once
#include <string>

class Material {
    public:
    std::string AlbedoTextureName;
    float specularColor[4] = {1.f,1.f,1.f,1.f};
    float emmisiveColor[4] = {0.f,0.f,0.f,1.f};
    float shininess = 1.f;
};