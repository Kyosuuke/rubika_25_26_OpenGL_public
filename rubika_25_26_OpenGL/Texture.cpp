#include "Texture.h"

#include <iostream>
#include <string>
#include <__msvc_ostream.hpp>
#include "stb/stb_image.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

bool Texture::Init(const char* texturePath)
{
    glGenTextures(1 , &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    unsigned char* image = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    stbi_set_flip_vertically_on_load(true);
    if (!image)
    {
        std::cout << "Failed to load texture" << std::endl;
        return false;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(image);
    return true;
}

void Texture::Use(Shader* shader, int index)
{
    if (index < 0 || index >= 15) return;

    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texture);

    std::string uniformName = std::string("texture") + std::to_string(index);
    shader->SetInt(uniformName.c_str(), index);
}
