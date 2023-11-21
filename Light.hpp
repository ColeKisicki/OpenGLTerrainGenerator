#pragma once
#include "Vector3.hpp"
#include "DisplayObject.hpp"
class Light
{
public:
    Light();
    public:
    Vector3 GetLocation();
    void SetLocation(Vector3 newLocation);

    bool IsOn = true;
    DisplayObject* LightMesh = nullptr;
    void SetAmbient(Vector3 newAmbient);
    void SetDiffuse(Vector3 newDiffuse);
    void SetSpecular(Vector3 newSpecular);

    

    float Ambient[4] = {0.10f, 0.10f, 0.10f, 1.0f};
    float Diffuse[4] = {0.50f, 0.50f, 0.50f, 1.0f};
    float Specular[4] = {0.01f, 0.01f, 0.01f, 1.0f};
protected:
    Vector3 Location;
};