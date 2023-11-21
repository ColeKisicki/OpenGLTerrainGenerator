#include "Light.hpp"

Light::Light()
{
    Location = Vector3(0.f,0.f,0.f);
}

Vector3 Light::GetLocation()
{
    return Location;
}

void Light::SetLocation(Vector3 newLocation)
{
    Location = newLocation;
    if(LightMesh)
    {
        LightMesh->Location = newLocation;
    }
}

void Light::SetDiffuse(Vector3 newDiffuse)
{
    Diffuse[0] = newDiffuse.x;
    Diffuse[1] = newDiffuse.y;
    Diffuse[2] = newDiffuse.z;
}

void Light::SetSpecular(Vector3 newSpecular)
{
    Specular[0] = newSpecular.x;
    Specular[1] = newSpecular.y;
    Specular[2] = newSpecular.z;
}

void Light::SetAmbient(Vector3 newAmbient)
{
    Ambient[0] = newAmbient.x;
    Ambient[1] = newAmbient.y;
    Ambient[2] = newAmbient.z;
}
