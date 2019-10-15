#include "Util.h"

unsigned int Util::LoadImage(const std::string& name, GLint internalFormat, GLenum format, int textSlot) {
	GLuint TextBuffer;

	glGenTextures(1, &TextBuffer);
	glActiveTexture(GL_TEXTURE0 + textSlot);
	glBindTexture(GL_TEXTURE_2D, TextBuffer);
	
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("load image failed!\n");
	}
	stbi_image_free(data);
	return TextBuffer;
}

Util::Util()
{
}


Util::~Util()
{
}
