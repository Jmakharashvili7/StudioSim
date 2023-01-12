#pragma once

#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"

#define MAX_FRAME_RATE 144

class Quack
{
public:

	Quack();
	~Quack();

	int InitEngine();

private:

	bool m_running;
	GLFWwindow* m_window;
};
