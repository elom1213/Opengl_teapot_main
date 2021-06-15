//21_6_2 teapot v shader 
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	FragPos = vec3(model*vec4(aPos, 1.0f));
	Normal = normalize(transpose(inverse(mat3(model)))*aNormal);
	TexCoord = aTexCoord;
	gl_Position = projection*view*vec4(FragPos, 1.0f);
}