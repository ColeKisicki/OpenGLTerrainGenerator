#include "Camera.hpp"
#include <iostream>
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
    if (NewCameraRotation == GetCameraRotation())
        return;
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

void Camera::UpdateCameraRotation()
{
    auto xRot = Rotation.z + accumulatedXRotation;
    auto yRot = Rotation.y + accumulatedYRotation;

    SetCameraRotation(glm::vec3(Rotation.x, yRot, xRot));

    accumulatedXRotation = 0.0f;
    accumulatedYRotation = 0.0f;
}

void Camera::RenderCamera()
{
    UpdateCameraRotation();
    glm::vec3 CurLocation = this->Location;
    glm::vec3 forward = CalculateForwardVector();

    glm::vec3 target = CurLocation + forward;

    // Assuming the camera's up direction is (0, 1, 0)
    gluLookAt(CurLocation.x, CurLocation.y, CurLocation.z, 
              target.x, target.y, target.z,
              0, 1, 0);
}

void Camera::HandleMouse(int x, int y)
{
    if (!isMouseInitialized)
    {
        lastMouseX = x;
        lastMouseY = y;
        isMouseInitialized = true;
    }

    int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

    int deltaX = x - lastMouseX;
    int deltaY = y - lastMouseY;

    accumulatedXRotation += static_cast<float>(deltaX) * 0.2f;
    accumulatedYRotation += static_cast<float>(deltaY) * -0.2f;

    const float threshold = 5.0f; // Adjust this threshold as needed

    if (abs(deltaX) > threshold || abs(deltaY) > threshold)
    {
        glutWarpPointer(centerX, centerY); // Re-center the cursor
        lastMouseX = centerX;
        lastMouseY = centerY;
    }
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

void Camera::HandleKeyPress(unsigned char key)
{
    const float moveSpeed = 0.5f; // Adjust movement speed as needed

    glm::vec3 forwardVector = CalculateForwardVector();
    glm::vec3 rightVector = CalculateRightVector();

    switch (key)
    {
    case 'w':
        Location += forwardVector * moveSpeed; // Move forward along the camera's forward vector
        break;
    case 'a':
        Location -= rightVector * moveSpeed; // Move to the left along the camera's right vector
        break;
    case 's':
        Location -= forwardVector * moveSpeed; // Move backward along the camera's forward vector
        break;
    case 'd':
        Location += rightVector * moveSpeed; // Move to the right along the camera's right vector
        break;
    }

    // Update the view after movement
    glutPostRedisplay();
}

glm::vec3 Camera::CalculateForwardVector() const
{
    float yaw = glm::radians(Rotation.z);
    float pitch = glm::radians(Rotation.y);

    float x = cos(yaw) * cos(pitch);
    float y = sin(pitch);
    float z = sin(yaw) * cos(pitch);

    return glm::normalize(glm::vec3(x, y, z));
}

glm::vec3 Camera::CalculateRightVector() const
{
    glm::vec3 forwardVector = CalculateForwardVector();
    glm::vec3 upVector(0.0f, 1.0f, 0.0f);

    return glm::normalize(glm::cross(forwardVector, upVector));
}
