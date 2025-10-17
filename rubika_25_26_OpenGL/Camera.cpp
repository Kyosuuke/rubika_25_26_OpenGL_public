#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(const glm::vec3& pos, const glm::vec3& worldUp, float pitch, float yaw)
{
    Position = pos;
    WorldUp = worldUp;
    Pitch = pitch;
    Yaw = yaw;

    
}

glm::mat4 Camera::GetMatrix() const
{
    
}

void Camera::UpdateCameraRotation()
{
    
}
