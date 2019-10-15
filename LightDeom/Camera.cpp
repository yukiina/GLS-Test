#include "Camera.h"


void Camera::MoveZ(float dir) {
	Position += Forward * dir;
	Position.y = 0;
}

void Camera::MoveX(float dir) {
	Position += Right * dir;
	Position.y = 0;
}



void Camera::HandleKeyPress(Movement direction, float deltaTime) {
	switch (direction)
	{
	case Camera::FORWARD:
		MoveZ(SPEED * deltaTime);
		break;
	case Camera::BACKWARD:
		MoveZ(-SPEED * deltaTime);
		break;
	case Camera::LEFT:
		MoveX(SPEED*deltaTime);
		break;
	case Camera::RIGHT:
		MoveX(-SPEED * deltaTime);
		break;
	default:
		break;
	}
}


void Camera::HandleMouseMove(float xoffset, float yoffset) {
	xoffset *= Camera::MOUSE_SENSITIVTY;
	yoffset *= Camera::MOUSE_SENSITIVTY;

	Pitch += yoffset;
	Yaw += xoffset;
	UpdateCameraVectors();
}

Camera::Camera(glm::vec3 position, float pitch, float yaw) : WorldUp(glm::vec3(0, 1.0f, 0)), Pitch(pitch), Yaw(yaw) {
	Position = position;
	Forward.x = glm::cos(glm::radians(pitch)) *  glm::sin(glm::radians(yaw));
	Forward.y = glm::sin(glm::radians(pitch));
	Forward.z = -glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
	Forward = glm::normalize(Forward);

	Right = glm::normalize(glm::cross(WorldUp, Forward));
	Up = glm::normalize(glm::cross(Forward, Right));
}


void  Camera::UpdateCameraVectors() {
	glm::vec3 forward;
	forward.x = glm::cos(glm::radians(Pitch)) *  glm::sin(glm::radians(Yaw));
	forward.y = glm::sin(glm::radians(Pitch));
	forward.z = -glm::cos(glm::radians(Pitch)) * glm::cos(glm::radians(Yaw));
	Forward = glm::normalize(forward);

	Right = glm::normalize(glm::cross(WorldUp, Forward));
	Up = glm::normalize(glm::cross(Forward, Right));
}

glm::mat4 Camera::GetViewMatrix() {

	return glm::lookAt(Position, Position + Forward, WorldUp);
}

Camera::~Camera()
{
}
