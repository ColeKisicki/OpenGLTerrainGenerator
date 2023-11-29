#include "Camera.hpp"

Camera::Camera()
{
    Location = glm::vec3(0,0,0);
    Rotation = glm::vec3(0,0,0);
    FOV = 70.f;
}

void Camera::SetCameraLocation(glm::vec3 NewCameraLocation)
{
    Location = NewCameraLocation;
}

void Camera::SetCameraRotation(glm::vec3 NewCameraRotation)
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

glm::vec3 Camera::GetCameraLocation()
{
    return Location;
}

glm::vec3 Camera::GetCameraRotation()
{
    return Rotation;
}

float Camera::GetCameraFOV()
{
    return FOV;
}
