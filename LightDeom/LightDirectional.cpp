#include "LightDirectional.h"

void LightDirectional::UpdateDir() {
	dir = glm::vec3(0, 0, 1.0f);
	dir = glm::rotateZ(dir, angle.z);
	dir = glm::rotateX(dir, angle.x);
	dir = glm::rotateY(dir, angle.y);
	dir *= -1;
}

LightDirectional::LightDirectional(glm::vec3 _position, glm::vec3 _angle, glm::vec3 _color)
	:position(_position), color(_color), angle(_angle)
{
	UpdateDir();
}


LightDirectional::~LightDirectional()
{
}
