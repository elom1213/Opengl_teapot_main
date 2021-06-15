#pragma once

#include <string>
#include <glad/glad.h>

using namespace std;

class Texture
{
public:
	Texture(const string& fileName, GLenum);
	void Bind(GLenum GLenum = GL_TEXTURE0);
	~Texture();
	GLuint texture;
};

