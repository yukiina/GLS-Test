#include "Mesh.h"



Mesh::Mesh(float _vertices[], int size)
{
	vertices.reserve(size / 8);
	for (int i = 0; i < size; i += 8) {
		Vertex v;

		v.Position = glm::vec3(*(_vertices + i), *(_vertices + 1 + i), *(_vertices + 2 + i));
		v.Normal = glm::vec3(*(_vertices + 3 + i), *(_vertices + 4 + i), *(_vertices + 5 + i));
		v.TexCoord = glm::vec2(*(_vertices + 6 + i), *(_vertices + 7 + i));
		vertices.push_back(v);
	}
	SetUpMesh();
}

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _texture)
{
	vertices = _vertices;
	indices = _indices;
	texture = _texture;
	SetUpMesh();
}

void Mesh::Draw(ShaderProgram & shader)
{
	for (size_t i = 0; i < texture.size(); i++)
	{
		if (texture[i].type == "texture_diffuse") {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture[i].ID);
			shader.SetUniform1im("material.diffuse", 0);
		}
		else if (texture[i].type == "texture_specular") {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture[i].ID);
			shader.SetUniform1im("material.specular", 1);
		}
	}


	glBindVertexArray(VAO);
	//printf("%u\n", VAO);
	if (indices.size() != 0) {
		//printf("%d\n", indices.size());
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}


Mesh::~Mesh()
{
}

void Mesh::SetUpMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	
	if (indices.size() != 0) {
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	}
	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	// TexCoord
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));

	glBindVertexArray(0);
}
