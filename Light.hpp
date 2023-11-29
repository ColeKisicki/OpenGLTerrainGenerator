#pragma once
#include "glm/glm.hpp"
#include "DisplayObject.hpp"
class Light
{
public:
    Light();
    public:
    glm::vec3 GetLocation();
    void SetLocation(glm::vec3 newLocation);

    bool IsOn = true;
    DisplayObject* LightMesh = nullptr;
    void SetAmbient(glm::vec3 newAmbient);
    void SetDiffuse(glm::vec3 newDiffuse);
    void SetSpecular(glm::vec3 newSpecular);

    

    float Ambient[4] = {0.10f, 0.10f, 0.10f, 1.0f};
    float Diffuse[4] = {0.50f, 0.50f, 0.50f, 1.0f};
    float Specular[4] = {0.01f, 0.01f, 0.01f, 1.0f};
protected:
    glm::vec3 Location;
};