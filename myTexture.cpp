#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
#include "myTexture.h"

Texture::Texture(const string& fileName, GLenum format)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imdata = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);

    if (imdata)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imdata);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        cout << "fail to load image file : " << fileName << endl;

    stbi_image_free(imdata);
}

void Texture::Bind(GLenum unit)
{
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, texture);
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture);
}
