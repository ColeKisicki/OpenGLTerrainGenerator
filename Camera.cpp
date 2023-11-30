#include "Camera.hpp"
#include "CSCIx229.hpp"

Camera::Camera()
{
    Location = glm::vec3(0, 0, 0);
    Rotation = glm::vec3(0, 0, 0);
    FOV = 70.f;
}

void Camera::SetCameraLocation(glm::vec3 NewCameraLocation)
{
    Location = NewCameraLocation;
}

void Camera::SetCameraRotation(glm::vec3 NewCameraRotation)
{
    Rotation = NewCameraRotation;
    if (Rotation.x > 360)
    {
        Rotation.x -= 360;
    }
    if (Rotation.y > 360)
    {
        Rotation.y -= 360;
    }
    if (Rotation.z > 360)
    {
        Rotation.z -= 360;
    }
}

void Camera::SetCameraFOV(float NewCameraFOV)
{
    FOV = NewCameraFOV;
}

void Camera::RenderCamera()
{
    glm::vec3 CurRotation = this->Rotation;
    glm::vec3 CurLocation = this->Location;

    double Ex = CurLocation.x - 2 * 4 * Sin(CurRotation.z) * Cos(CurRotation.y);
    double Ey = CurLocation.y + 2 * 4 * Sin(CurRotation.y);
    double Ez = CurLocation.z + 2 * 4 * Cos(CurRotation.z) * Cos(CurRotation.y);
    gluLookAt(CurLocation.x, CurLocation.y, CurLocation.z, Ex, Ey, Ez, 0, Cos(CurRotation.y), 0);
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
