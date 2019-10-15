#include "LightPoint.h"



LightPoint::LightPoint(glm::vec3 _position, glm::vec3 _angle, glm::vec3 _color)
	:position(_position), color(_color), angle(_angle)

{
}


LightPoint::~LightPoint()
{
}
