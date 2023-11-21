#include "Camera.hpp"

Camera::Camera()
{
    Location = Vector3(0,0,0);
    Rotation = Vector3(0,0,0);
    FOV = 70.f;
}

void Camera::SetCameraLocation(Vector3 NewCameraLocation)
{
    Location = NewCameraLocation;
}

void Camera::SetCameraRotation(Vector3 NewCameraRotation)
{
    Rotation = NewCameraRotation;
    if(Rotation.x > 360) {
        Rotation.x -= 360;
    }
    if(Rotation.y > 360) {
        Rotation.y -= 360;
    }
    if(Rotation.z > 360) {
        Rotation.z -= 360;
    }
}

void Camera::SetCameraFOV(float NewCameraFOV)
{
    FOV = NewCameraFOV;
}

Vector3 Camera::GetCameraLocation()
{
    return Location;
}

Vector3 Camera::GetCameraRotation()
{
    return Rotation;
}

float Camera::GetCameraFOV()
{
    return FOV;
}
