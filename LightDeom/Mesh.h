#pragma once

#include "GL/glew.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "ShaderProgram.h"

struct Vertex {

	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
};

struct Texture {
	unsigned int ID;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> texture;

	Mesh(float _vertices[], int size);
	Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _texture);
	void Draw(ShaderProgram& shader);
	~Mesh();
private:
	unsigned int VAO, VBO, EBO;
	void SetUpMesh();
};

