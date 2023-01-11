#pragma once

#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "OrthographicCamera.h"

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
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
public:
	bool m_capFrames;
private:
	GLFWwindow* m_window;

	bool m_running;

	//Frame related variables
	double m_currentTime;
	double m_lastTime;
	double m_deltaTime;
	double m_frameTime;
	double m_frameDelay;

	int m_frameCounter;
	int m_currentFrameRate;

	OrthographicCamera m_mainCamera;
};
