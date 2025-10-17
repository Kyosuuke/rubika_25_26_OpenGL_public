#include "Camera.h"

#include <algorithm>
#include <glm/ext/matrix_transform.hpp>

Camera::Camera()
{
    Position = glm::vec3(0.0f, 0.0f, 3.0f);
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    Yaw = -90.0f;
    Pitch = 0.0f;
    Front = glm::vec3(0.0f, 0.0f, -1.0f);
    MovementSpeed = 2.5f;
    MouseSensitivity = 0.1f;
    Fov = 45.0f;
    UpdateCameraRotation();
}

Camera::Camera(const glm::vec3& pos, const glm::vec3& worldUp, float pitch, float yaw)
{
    Position = pos;
    WorldUp = worldUp;
    Pitch = pitch;
    Yaw = yaw;
    Front = glm::vec3(0.0f, 0.0f, -1.0f);
    MovementSpeed = 2.5f;
    MouseSensitivity = 0.1f;
    Fov = 45.0f;
    UpdateCameraRotation();
}

glm::mat4 Camera::GetMatrix() const
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Direction direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == Direction::Forward)
        Position += Front * velocity;
    else if (direction == Direction::Backward)
        Position -= Front * velocity;
    else if (direction == Direction::Right)
        Position += Right * velocity;
    else if (direction == Direction::Left)
        Position -= Right * velocity;
}

void Camera::ProcessMouse(float xoffset, float yoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    Pitch = std::min(Pitch, 89.0f);
    Pitch = std::max(Pitch, -89.0f);

    UpdateCameraRotation();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Fov -= yoffset;
    Fov = std::max(Fov, 1.0f);
    Fov = std::min(Fov, 45.0f);
}

void Camera::UpdateCameraRotation()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
