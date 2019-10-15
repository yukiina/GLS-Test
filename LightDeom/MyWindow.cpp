#include "MyWindow.h"


using std::string;


float MyWindow::lastX = 0.0f;
float MyWindow::lastY = 0.0f;
float MyWindow::offsetX = 0.0f;
float MyWindow::offsetY = 0.0f;
bool MyWindow::firstMouse = true;
Camera* MyWindow::wcamera = nullptr;
MyWindow::MyWindow(int width, int height, const string& name){
	GlfwInit();
	window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

	if (window == nullptr) {
		printf("create window failed!");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("init glew failed !");
		glfwTerminate();
	}

	glViewport(0, 0, width, height);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 隐藏光标
	glEnable(GL_DEPTH_TEST);//开启深度测试
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int newWidth, int newHeight){ //注册窗口大小改变回调事件
		glViewport(0, 0, newWidth, newHeight);

	});
	
}
void MyWindow::OffsetXYCallBack(float x, float y) {
	
	wcamera->HandleMouseMove(x, y);
}
void MyWindow::EnableMouseMoveEvent(Camera* camera) {
	wcamera = camera;
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
			return;
		}
		float offsetX = xpos - lastX;
		float offsetY = lastY - ypos;
		
		OffsetXYCallBack(offsetX, offsetY);
		lastX = xpos;
		lastY = ypos;
		});
}

void MyWindow::CalcDeltaTime() {
	currentTime = glfwGetTime();
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;
}

float MyWindow::GetDeltaTime() {
	return deltaTime;
}

void MyWindow::AddKeyPressEvent(Key key, KeyPressFun fun){
	keyMap[key] = fun;
}

void MyWindow::ProcessKeyPress() {
	for (auto& pair : keyMap) {
		if (glfwGetKey(window, pair.first) == GLFW_PRESS) {
			pair.second();
		}
	}
}

void MyWindow::CloseWindow() {
	glfwSetWindowShouldClose(window, true);
}

void MyWindow::RunLoop(RenderEvent rLoop) {
	while (!glfwWindowShouldClose(window)) {
		ProcessKeyPress();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		CalcDeltaTime();

		// Game Rendering Loop
		rLoop();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
}

void MyWindow::GlfwInit() {
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

MyWindow::~MyWindow()
{
}
