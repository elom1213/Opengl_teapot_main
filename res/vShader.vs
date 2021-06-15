#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float alp;

void main()
{
	gl_Position = vec4(alp, aPos.yz, 1.0f);
	ourColor = vec3(aColor.xyz);
}
