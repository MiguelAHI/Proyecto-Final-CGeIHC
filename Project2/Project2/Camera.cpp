#include "Camera.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	defaultCamera = 1;
	upCamera = 0;
	
	positionTemp = position = startPosition;
	xAerea = 10.0f;
	zAerea = 0.0f;
	posAereaTemp = glm::vec3(xAerea, 80.0f, zAerea);
	worldUpAnt = worldUp = startUp;
	yawAnt = yaw = startYaw;
	pitchAnt = pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::changeCamera(bool *keys) {
	// Almacenamiento de posición actual de cámaras
	if ((defaultCamera) && !(keys[GLFW_KEY_Z])) {
		positionTemp = position;
		yawAnt = yaw;
		pitchAnt = pitch;
		worldUpAnt = worldUp;
	}

	if ((upCamera) && !(keys[GLFW_KEY_X])) {
		posAereaTemp = position;
	}

	// Restaura de memoria los valores de posiciones temporales
	if (keys[GLFW_KEY_Z])
	{
		defaultCamera = 1;
		upCamera = 0;

		position = positionTemp;
		yaw = yawAnt;
		pitch = pitchAnt;
		worldUp = worldUpAnt;

		update();
	}

	if (keys[GLFW_KEY_X])
	{
		defaultCamera = 0;
		upCamera = 1;

		position = posAereaTemp;
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		yaw = 0.0f;
		pitch = -89.0f;
	}
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (defaultCamera) {
		if (keys[GLFW_KEY_W])
		{
			position += front * velocity;
		}

		if (keys[GLFW_KEY_S])
		{
			position -= front * velocity;
		}

		if (keys[GLFW_KEY_A])
		{
			position -= right * velocity;
		}

		if (keys[GLFW_KEY_D])
		{
			position += right * velocity;
		}
	}
	else { // upCamera
		if (keys[GLFW_KEY_W])
		{
			xAerea += 0.5f;
		}

		if (keys[GLFW_KEY_S])
		{
			xAerea -= 0.5f;
		}

		if (keys[GLFW_KEY_A])
		{
			zAerea -= 0.5f;
		}

		if (keys[GLFW_KEY_D])
		{
			zAerea += 0.5f;
		}
		position = glm::vec3(xAerea, 80.0f, zAerea);
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}


glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera()
{
}
