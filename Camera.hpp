#pragma once
#include "Vector3.hpp"

class Camera
{
private:
    Vector3 Location;
    Vector3 Rotation;
    float FOV = 70.f;

public:
    Camera();
    void SetCameraLocation(Vector3 NewCameraLocation);
    void SetCameraRotation(Vector3 NewCameraRotation);
    void SetCameraFOV(float NewCameraFOV);

    Vector3 GetCameraLocation();
    Vector3 GetCameraRotation();
    float GetCameraFOV();
};
