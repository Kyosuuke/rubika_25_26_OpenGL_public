#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    Shader();
    ~Shader();

    bool InitShader(const char* vertexPath, const char* fragmentPath);

    void SetInt(const std::string& name, int value) const;   
    void SetFloat(const std::string& name, float value) const;

    void SetMatrix(const std::string& name, const glm::mat4& mat) const;
    
    void Use();
    
private:
    GLuint programID;
    
};
