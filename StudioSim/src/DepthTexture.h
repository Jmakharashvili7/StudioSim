#pragma once
#include "Renderer.h"
#include "BasicIncludes.h"

using namespace std;

class DepthTexture
{
public:
	DepthTexture(const string& path);
	~DepthTexture();

	void DepthBind(unsigned int slot = 0) const;
	void DepthUnBind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMap;
private:
	unsigned int m_rendererID;
	string m_filePath;
	unsigned char* m_localBuffer;
	// Width, height, bits per pixel of the texture
	int m_width, m_height, m_BPP;
};