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


#define MAX_FRAME_RATE 144
#define GFORCE 9.81
#define JUMP_HEIGHT 3.0f

class QuackPhysics;

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

	static void ImGUIInit();
	static void Jump();
	static void JumpDecrement();
	static void Gravity();

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

	static bool m_jumping;
	static float m_jump_force;


	// Square
	/*static IndexBuffer* m_ib;
	static VertexBuffer* m_vb;
	static VertexBuffer* m_vertexBuffer;
	static VertexArray m_va;
	static VertexBufferLayout m_vbLayout;*/
	static unsigned int m_square1VBO;
	static unsigned int m_square1VAO;

	static glm::vec3 squarePositionData[];
	static glm::vec3 squareScaleData[];
	
	static Texture* m_duckTexture;
	
	static QuackPhysics* p_QuackPhysics;
	
	static Shader* m_mainShader;
	static OrthographicCamera* m_mainCamera;
};
