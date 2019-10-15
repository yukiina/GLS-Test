#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
class LightPoint
{
public:
	LightPoint(glm::vec3 _position, glm::vec3 _angle, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint();
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 angle;
	glm::vec3 dir = glm::vec3(0, 0, 1.0f);

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;
};

