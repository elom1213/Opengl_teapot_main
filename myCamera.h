#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ZOOM = 45.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;

class myCamera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;

	float yaw;
	float pitch;

	float MouseSpeed;
	float MouseSensitivity;
	float Zoom;

	myCamera();
	void processkeyboard(Camera_movement direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset);
	glm::mat4 getViewMatrix();

private:
	void updateCameraVectors();
};

