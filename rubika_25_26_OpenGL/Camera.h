#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

class Camera
{
public:
    enum class Direction
    {
        Forward,
        Backward,
        Right,
        Left
    };

    Camera();
    Camera(const glm::vec3& pos, 
        const glm::vec3& worldUp,
        float pitch,
        float yaw);

    // use glm::lookAt
    glm::mat4 GetMatrix() const;

    // Input
    void ProcessKeyboard(Direction direction, float deltaTime);
    void ProcessMouse(float xoffset, float yoffset);
    void ProcessMouseScroll(float yoffset);
    
    float GetCameraSpeed() {return MovementSpeed;}
    float GetFov() {return Fov;}
    glm::vec3 GetPosition() {return Position;}

private:
    // Compute the Front and Right vector using the euler angles
    void UpdateCameraRotation();

    // Translation
    glm::vec3 Position;

    // Rotation - Must be normalized
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler Angles
    float Yaw;
    float Pitch;
    
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Fov;
};
