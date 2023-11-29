#pragma once
#include "glm/glm.hpp"

class Camera
{
private:
    glm::vec3 Location;
    glm::vec3 Rotation;
    float FOV = 70.f;

public:
    Camera();
    void SetCameraLocation(glm::vec3 NewCameraLocation);
    void SetCameraRotation(glm::vec3 NewCameraRotation);
    void SetCameraFOV(float NewCameraFOV);

    glm::vec3 GetCameraLocation();
    glm::vec3 GetCameraRotation();
    float GetCameraFOV();
};
