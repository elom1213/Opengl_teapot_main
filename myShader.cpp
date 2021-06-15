// myShader.cpp 21_6_2
#include <fstream>
#include <sstream>
#include <iostream>
#include "myShader.h"

Shader::Shader(const char *vShaderPath, const char *fShaderPath)
{
	ifstream vShaderFile, fShaderFile;
	stringstream vShaderStream, fShaderStream, errorString;

	vShaderFile.open(vShaderPath);
	fShaderFile.open(fShaderPath);

	if (!vShaderFile || !fShaderFile)
		cout << "Shader file open fail" << endl;

	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();

	vShaderFile.close();
	fShaderFile.close();

	vShaderStr = vShaderStream.str();
	fShaderStr = fShaderStream.str();

	const char* vShaderPtr = vShaderStr.c_str();
	const char* fShaderPtr = fShaderStr.c_str();

	unsigned int vShaderObj = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fShaderObj = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShaderObj, 1, &vShaderPtr, NULL);
	glCompileShader(vShaderObj);
	errorString << "error compile : " << vShaderPath << '\n';
	CheckShaderError(vShaderObj, GL_COMPILE_STATUS, false, errorString.str());
	errorString.clear();

	glShaderSource(fShaderObj, 1, &fShaderPtr, NULL);
	glCompileShader(fShaderObj);
	errorString << "error compile : " << fShaderPath << '\n';
	CheckShaderError(fShaderObj, GL_COMPILE_STATUS, false, errorString.str());
	errorString.clear();

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShaderObj);
	glAttachShader(shaderProgram, fShaderObj);
	glLinkProgram(shaderProgram);
	CheckShaderError(shaderProgram, GL_LINK_STATUS, true, "error linking shader program");

	glDeleteShader(vShaderObj);
	glDeleteShader(fShaderObj);
}

void Shader::use()
{
	glUseProgram(shaderProgram);
}

void Shader::setBool(const string &name, const bool value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

void Shader::setInt(const string &name, const int &value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()),value);
}

void Shader::setFloat(const string &name, const float &value) const
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setVec3(const string& name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat4(const string &name, const glm::mat4 &mat4) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4));
}

unsigned int Shader::getProg()
{
	return shaderProgram;
}

void Shader::CheckShaderError(GLuint shader, GLint flag, bool is_program, const string &errormsg) const
{
	GLint is_succeeded;
	GLchar infoLog[1024] = { 0 };

	if (is_program)
		glGetProgramiv(shader, flag, &is_succeeded);
	else
		glGetShaderiv(shader, flag, &is_succeeded);

	if (is_succeeded == GL_FALSE)
	{
		if (is_program)
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
		else
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		cout << errormsg << " : '" << infoLog << "'" << endl;
	}
}

Shader::~Shader()
{
	glDeleteProgram(shaderProgram);
}