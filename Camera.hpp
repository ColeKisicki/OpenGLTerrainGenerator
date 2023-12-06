#pragma once
#include "glm/glm.hpp"

class Camera
{
private:
    glm::vec3 Location;
    glm::vec3 Rotation; // x = roll, y=pitch, z=yaw
    float FOV = 70.f;
    bool isMouseInitialized = false;
    float lastMouseX = 0.f;
    float lastMouseY = 0.f;
    float accumulatedXRotation = 0.0f;
    float accumulatedYRotation = 0.0f;
    
    void UpdateCameraRotation();

public:
    Camera();
    void SetCameraLocation(glm::vec3 NewCameraLocation);
    void SetCameraRotation(glm::vec3 NewCameraRotation);
    void SetCameraFOV(float NewCameraFOV);
    void RenderCamera();
    void HandleMouse(int x, int y);

    glm::vec3 GetCameraLocation();
    glm::vec3 GetCameraRotation();
    void HandleKeyPress(unsigned char key);
    glm::vec3 CalculateForwardVector() const;
    glm::vec3 CalculateRightVector() const;
    float GetCameraFOV();
};
