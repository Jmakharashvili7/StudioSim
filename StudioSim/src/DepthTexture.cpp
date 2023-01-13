#include "DepthTexture.h"
#include "stb_image/stb_image.h"

DepthTexture::DepthTexture(const string& path) :
	m_rendererID(0), m_filePath(path), m_localBuffer(nullptr), m_width(0), m_height(0), m_BPP(0)
{
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 0);
	if (m_localBuffer)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(m_localBuffer);
}

DepthTexture::~DepthTexture()
{
	GLCall(glDeleteTextures(1, &m_rendererID));
}

void DepthTexture::DepthBind(unsigned int slot) const
{
	//GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void DepthTexture::DepthUnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}