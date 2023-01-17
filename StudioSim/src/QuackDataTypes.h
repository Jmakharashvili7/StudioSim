#pragma once
#include "BasicIncludes.h"

struct TextureData
{
	TextureData(const std::string& inTexturePath) : texturePath(inTexturePath),
		internalFormat(GL_RGB), imageFormat(GL_RGB) {};

	TextureData(const std::string& inTexturePath, GLint inInternalFormat, GLint inImageFormat)
		: texturePath(inTexturePath), internalFormat(inInternalFormat),
		imageFormat(inImageFormat) {};

	std::string texturePath;
	GLint internalFormat;
	GLint imageFormat;
};


