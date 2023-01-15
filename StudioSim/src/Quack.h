#pragma once

#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "OrthographicCamera.h"
#include "Window.h"
#include "Texture.h"
#include "GameObject.h"

#define MAX_FRAME_RATE 144

class Quack
{
public:
	static int InitEngine();
	static void InitObjects();

	static void Update();
	static void RenderUpdate();
	//void PhysicsUpdate();

	static void ShutDown();

	static void GetFrameRate(float deltatime);
private:
	Quack();
	~Quack();

	static void HandleInput();
public:
	static bool m_capFrames;
	static bool s_running;
	static bool s_glfwInitialised;
private:
	static Window* m_window;

	//Frame related variables
	static double m_currentTime;
	static double m_lastTime;
	static double m_deltaTime;
	static double m_frameTime;
	static double m_frameDelay;

	static int m_frameCounter;
	static int m_currentFrameRate;

	static GameObject* m_duck;

	// Square
	/*static IndexBuffer* m_ib;
	static VertexBuffer* m_vb;
	static VertexBuffer* m_vertexBuffer;
	static VertexArray m_va;
	static VertexBufferLayout m_vbLayout;*/
	static VertexArray* m_squareVAO;
	static Texture* m_duckTexture;
	static glm::vec4 m_objColor;

	static glm::vec3 m_lightPos;

	static Shader* m_mainShader;
	static OrthographicCamera* m_mainCamera;
};
