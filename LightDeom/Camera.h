#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Camera
{
public:
	enum Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
	};
public:
	 float MOUSE_SENSITIVTY = 0.05f; // 相机灵敏度
	 float SPEED = 3.0f;             // 相机移动速度
public:
	Camera(glm::vec3 position, float pitch, float yaw);
	~Camera();
public:
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;

	float Pitch;
	float Yaw;

public:
	glm::mat4 GetViewMatrix();
	void HandleMouseMove(float xoffset, float yoffset);
	void HandleKeyPress(Movement direction, float deltaTime);
	void MoveZ(float dir);
	void MoveX(float dir);
	void MoveY(float dir);
private:
	void UpdateCameraVectors();
};

