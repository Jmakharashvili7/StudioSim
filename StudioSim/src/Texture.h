#pragma once
#include "BasicIncludes.h"

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
private:
	unsigned int m_rendererID;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	// Width, height, bits per pixel of the texture
	int m_width, m_height, m_BPP;
};
