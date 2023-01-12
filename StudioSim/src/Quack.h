#pragma once

#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "OrthographicCamera.h"
#include "Window.h"

#define MAX_FRAME_RATE 144

class Quack
{
public:

	Quack();
	~Quack();

	int InitEngine();

	void Update();
	void RenderUpdate();
	void PhysicsUpdate();

	void ShutDown();

	void GetFrameRate(float deltatime);
private:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void HandleInput();
public:
	bool m_capFrames;
	static bool glfwInitialised;
private:
	Window m_window;
	bool m_running;

	//Frame related variables
	double m_currentTime;
	double m_lastTime;
	double m_deltaTime;
	double m_frameTime;
	double m_frameDelay;

	int m_frameCounter;
	int m_currentFrameRate;

	// Square
	//IndexBuffer m_ib;
	//VertexBuffer m_vb;
	//VertexArray m_va;
	//VertexBuffer m_vertexBuffer;
	//VertexBufferLayout m_vbo;

	Shader* m_mainShader;
	OrthographicCamera m_mainCamera;
};
