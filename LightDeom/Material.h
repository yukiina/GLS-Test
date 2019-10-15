#pragma once
#include "ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public:
	Material(ShaderProgram* _shader, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess);
	Material(ShaderProgram* _shader, glm::vec3 _ambient, unsigned int _diffuse, unsigned int _specular, float _shininess);
	~Material();

private:
	ShaderProgram* shader;
public:
	unsigned int diffuseText;
	unsigned int specularText;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

