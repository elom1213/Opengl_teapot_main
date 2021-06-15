// myShader.h 21_5_7
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Shader
{
public:
	Shader(const char*, const char*);
	~Shader();
	void use();
	void setBool(const string &, const bool) const;
	void setInt(const string &, const int &) const;
	void setFloat(const string &, const float &) const;
	void setVec3(const string&, const glm::vec3 &) const;
	void setMat4(const string &, const glm::mat4 &) const;
	void CheckShaderError(GLuint shader, GLint flag, bool isProgram, const string& errormsg) const;
	unsigned int getProg();
private:
	unsigned int shaderProgram;
	string vShaderStr, fShaderStr;
};

#endif //SHEDER_H
