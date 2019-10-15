#pragma once
#define GLEW_STATIC
#include "GL/glew.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
public:
	enum ShaderType {
		VERTEX_SHADER = GL_VERTEX_SHADER, 
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER
	};
public:
	ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
	~ShaderProgram();
public:
	void Use() const;
	void SetUniform3f(const std::string& paramName, glm::vec3 param);
	void SetUniform1f(const std::string& paramName, float param);
	void SetUniform1im(const std::string& paramName, int slot);
private:
	void ReadShader(std::string& ret, const std::string& filePath);
	GLuint CompileShader(std::string& shaderSource, ShaderType type);
	void LinkShader(GLuint vShader, GLuint fShader);

public: // TODO:
	GLuint program;
	bool isCompilerSuccess;
};

