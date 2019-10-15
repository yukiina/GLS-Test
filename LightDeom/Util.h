#pragma once
#include <string>
#include "GL/glew.h"
#include "stb_image.h"

class Util
{
public:
	static unsigned int LoadImage(const std::string& name, GLint internalFormat, GLenum format, int textSlot);
private:
	Util();
	~Util();
};

