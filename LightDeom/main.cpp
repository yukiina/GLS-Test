#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <string>
#include "ShaderProgram.h"
#include "MyWindow.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Material.h"
#include "Util.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "Mesh.h"
#include "Model.h"

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};


int main(int argc, char** argv) {

	std::string exePath = argv[0];
	MyWindow window(800, 600, "Deom");
	Camera camera(glm::vec3(0, 0, 5.0f), 0,0);

	#pragma region 注册按键事件
	// 注册按键事件
	window.AddKeyPressEvent(MyWindow::Key::KEY_ESCAPE, [&window]() {
		window.CloseWindow();
	});
	window.AddKeyPressEvent(MyWindow::KEY_W, [&camera, &window]() {
		camera.HandleKeyPress(Camera::FORWARD, window.GetDeltaTime());
	});
	window.AddKeyPressEvent(MyWindow::KEY_S, [&camera, &window]() {
		camera.HandleKeyPress(Camera::BACKWARD, window.GetDeltaTime());
	});
	window.AddKeyPressEvent(MyWindow::KEY_A, [&camera, &window]() {
		camera.HandleKeyPress(Camera::LEFT, window.GetDeltaTime());
	});
	window.AddKeyPressEvent(MyWindow::KEY_D, [&camera, &window]() {
		camera.HandleKeyPress(Camera::RIGHT, window.GetDeltaTime());
	});

#pragma endregion
	window.EnableMouseMoveEvent(&camera);

	
	ShaderProgram shader("vertex.vert", "fragment.frag");
	//ShaderProgram shader2("model.vert", "model.frag");
	//Material material(&shader, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 64.0f);
	Material material(&shader, glm::vec3(0.1f, 0.1f, 0.1f),Util::LoadImage("container2.png", GL_RGBA, GL_RGBA, 0), Util::LoadImage("container2_specular.png", GL_RGBA, GL_RGBA, 1), 64.0f);
	//Material material2(&shader2, glm::vec3(0.1f, 0.1f, 0.1f), Util::LoadImage("container2.png", GL_RGBA, GL_RGBA, 0), Util::LoadImage("container2_specular.png", GL_RGBA, GL_RGBA, 1), 64.0f);
	LightPoint lightDir(glm::vec3(1, 1, -1), glm::vec3(glm::radians(45.0f), 0, 0));
	Mesh cube(vertices, sizeof(vertices) / sizeof(vertices[0]));
	Model model(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\nanosuit.obj");



	window.RunLoop([&]() {
		
		shader.Use();
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		
		glm::mat4 trans;
		
		trans = glm::scale(trans, glm::vec3(10.f, 0.1f, 10.0f));
		trans = glm::translate(trans, glm::vec3(0.0f, -3.0f, 0));
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(trans));
		glUniform3f(glGetUniformLocation(shader.program, "objColor"), 0.5f, 0.5f, 0.5f);
		shader.SetUniform3f("lightColor", lightDir.color);
		shader.SetUniform3f("lightPos", lightDir.position);
		shader.SetUniform1f("constant", lightDir.constant);
		shader.SetUniform1f("linear", lightDir.linear);
		shader.SetUniform1f("quadratic", lightDir.quadratic);
		//shader.SetUniform3f("lightDirU", lightDir.dir);
		glUniform3f(glGetUniformLocation(shader.program, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);


		shader.SetUniform3f("material.ambient", material.ambient);

		shader.SetUniform1f("material.shininess", 64.0f);
		

		cube.Draw(shader);

		glm::mat4 trans2;
		trans2 = glm::scale(trans2, glm::vec3(0.15f, 0.15f, 0.15f));
		trans2 = glm::translate(trans2, glm::vec3(0.0f, -2.0f, 0));
		glUniform3f(glGetUniformLocation(shader.program, "objColor"), 1.0f,0, 0);
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(trans2));
		model.Draw(shader);
	});
	return 0;
}
