#pragma once

#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Renderer.h"

#define MAX_FRAME_RATE 144

class Quack
{
public:

	Quack();
	~Quack();

	int InitEngine();

	void RenderUpdate(float deltatime);
	void PhysicsUpdate(float deltatime);

	void GetFrameRate(float deltatime);

private:

	GLFWwindow* m_window;
	Renderer* m_renderer;


	bool m_running;

	//Frame related variables
	double m_currentTime;
	double m_lastTime;
	double m_deltaTime;
	double m_frameTime;
	double m_frameDelay;

	int m_frameCounter;
	int m_currentFrameRate;

public:
	bool m_capFrames;
};
