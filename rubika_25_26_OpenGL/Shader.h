#pragma once

#include <glad/glad.h>

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
    
    void Use();
    
private:
    GLuint programID;
};
