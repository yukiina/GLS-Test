#include "ShaderProgram.h"


using std::string;

void ShaderProgram::Use()const {
	if (!isCompilerSuccess) {
		printf("this shader compiler failed, used failed!!\n");
		assert(0);
	}

	glUseProgram(program);
}

void ShaderProgram::SetUniform3f(const std::string& paramName, glm::vec3 param) {
	glUniform3f(glGetUniformLocation(program, paramName.c_str()), param.x, param.y, param.z);
}
void ShaderProgram::SetUniform1f(const std::string& paramName, float param) {
	glUniform1f(glGetUniformLocation(program, paramName.c_str()), param);
}
void ShaderProgram::SetUniform1im(const std::string& paramName, int slot) {
	glUniform1i(glGetUniformLocation(program, paramName.c_str()), slot);
}

ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) : isCompilerSuccess(true)
{
	string vertexStr;
	string fragmentStr;
	ReadShader(vertexStr, vertexPath);
	ReadShader(fragmentStr, fragmentPath);

	GLuint vertexShader = CompileShader(vertexStr, ShaderType::VERTEX_SHADER);
	GLuint fragmentShader = CompileShader(fragmentStr, ShaderType::FRAGMENT_SHADER);
	LinkShader(vertexShader, fragmentShader);
}

void ShaderProgram::ReadShader(std::string& ret, const std::string& filePath) {
	//1. 读取Shader文件流到字符串中
	std::ifstream inFile;
	inFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		inFile.open(filePath.c_str());
		std::stringstream sStream;
		sStream << inFile.rdbuf();
		inFile.close();
		ret = sStream.str();
	}
	catch (std::ifstream::failure e)
	{
		printf("Error: %s shader file read failed!!!\n", filePath.c_str());
		isCompilerSuccess = false;
	}
}

GLuint ShaderProgram::CompileShader(std::string& shaderSource, ShaderType type) {
	//2. 编译着色器
	const char* source = shaderSource.c_str();

	int success;       //编译错误信息
	char infoLog[512]; // 编译错误日志

	GLuint shader = glCreateShader(type);// 着色器对象

	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		switch (type)
		{
		case ShaderProgram::VERTEX_SHADER:
			printf("vertex shader comiple failed, error: %s", infoLog);
			break;
		case ShaderProgram::FRAGMENT_SHADER:
			printf("fragment shader comiple failed, error: %s", infoLog);
			break;
		}
		isCompilerSuccess = false;
	}
	return shader;
}

//3. 链接到Shader program 对象
void ShaderProgram::LinkShader(GLuint vShader, GLuint fShader) {
	
	int success;       //链接错误信息
	char infoLog[512]; // 链接错误日志

	program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		printf("shader program link error: %s\n" , infoLog);
		isCompilerSuccess = false;
	}

	// 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

ShaderProgram::~ShaderProgram()
{
}
