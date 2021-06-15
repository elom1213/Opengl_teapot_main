#include "myCamera.h"

myCamera::myCamera():
	Position{glm::vec3(0.0, 0.0, 3.0)},
	WorldUp{glm::vec3(0.0, 1.0, 0.0)},
	yaw{ YAW }, pitch{ PITCH }, Zoom{ZOOM},
	MouseSensitivity{SENSITIVITY},
	MouseSpeed{SPEED}
{
	updateCameraVectors();
}

void myCamera::processkeyboard(Camera_movement direction, float deltaTime)
{
	float velocity = MouseSpeed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;
	else if (direction == BACKWARD)
		Position -= Front * velocity;
	else if (direction == LEFT)
		Position -= Right * velocity;
	else if (direction == RIGHT)
		Position += Right * velocity;
}

void myCamera::updateCameraVectors()
{
	glm::vec3 front;
	float yaw_rad = glm::radians(yaw);
	float pitch_rad = glm::radians(pitch);

	front.x = cos(yaw_rad) * cos(pitch_rad);
	front.y = sin(pitch_rad);
	front.z = sin(yaw_rad) * cos(pitch_rad);
	
	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

void myCamera::processMouseMovement(float xoffset, float yoffset)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	updateCameraVectors();
}

glm::mat4 myCamera::getViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}