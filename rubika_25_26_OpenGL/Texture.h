#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>

#include "Shader.h"

class Texture
{
public:
    Texture();
    ~Texture();
    
    // Read both file to init the vertex shader and the fragment shader
    bool Init(const char* texturePath);

    // Use the corresponding texture
    void Use(Shader* progamID, int index);

    unsigned int texture;
    int width, height, nrChannels;
};
