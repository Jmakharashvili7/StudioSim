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
#include "GameTime.h"
#include "Actor.h"
#include "QuackDataTypes.h"
#include "PhysicsManager.h"
#include "FrameBuffer.h"
#include "Grid.h"
#include "PathNode.h"
#include "CollisionManager.h"
#include "Scene.h"

class LayerStack;
class UIRenderer;
class UILayer;

#define MAX_FRAME_RATE 144
#define NUMBER_OF_SQUARES 4

class QuackPhysics;

class Quack
{
public:
	static int InitEngine();

	static void Update();
	static void RenderUpdate();
	static void PhysicsUpdate();
	static void HandleLights();

	static void ShutDown();
	static Window* GetWindow() { return m_window; }

	static void ImGUIInit();

	static OrthographicCamera* GetOrthoCamera() { return m_mainCamera; }
	static void SetOrthoCamera(OrthographicCamera* camera) { m_mainCamera = camera; }

	static inline float GetDeltaTime() { return m_gameTimer.GetDeltaTime(); }
	static FrameBuffer* GetFrameBuffer() { return m_frameBuffer; }
	static UILayer* GetUILayer() { return m_uiMain; }

	static OrthographicCamera* GetOrthoCam() { return m_mainScene.GetCamera(); }
	//static BoundingBox CreateBoundingBox(glm::vec3 positions,glm::vec3 scale);
private:
	Quack();
	~Quack();

	static void HandleInput();
	static void InitObjects();
public:
	static bool m_capFrames;
	static bool s_running;
	static bool s_glfwInitialised;
private:
	static Window* m_window;
	static LayerStack* m_layerStack;
	static UILayer* m_uiMain;
	static PhysicsManager* m_physicsManager;
	static CollisionManager* m_collisionManager;

	//Frame related variables
	static double m_currentTime;
	static double m_lastTime;
	static double m_deltaTime;
	static double m_frameTime;
	static double m_frameDelay;
	static Grid<PathNode> m_grid;

	static GameTimer m_gameTimer;
	static Scene m_mainScene;

	static int m_frameCounter;
	static int m_currentFrameRate;

	static FrameBuffer* m_frameBuffer;
	
	static Actor* m_duck;
	static GameObject* m_ground;
	static GameObject* m_testSprite;

	static std::vector<GameObject*> m_gameObjects;
	static std::vector<Actor*> m_gameActors;

	static VertexArray* m_squareVAO;
	static glm::vec4 m_objColor;

	static QuackPhysics* p_QuackPhysics;

	//lights
	static glm::vec4 m_lightPos;
	static glm::vec4 m_dirAmbient;
	static glm::vec4 m_dirDiffuse;
	static glm::vec4 m_dirSpecular;

	static glm::vec3 m_pointLightPositions[];
	static glm::vec4 m_pointAmbient;
	static glm::vec4 m_pointDiffuse;
	static glm::vec4 m_pointSpecular;

	static glm::vec4 m_spotAmbient;
	static glm::vec4 m_spotDiffuse;
	static glm::vec4 m_spotSpecular;
	static glm::vec4 m_lightAmbient;

	static OrthographicCamera* m_mainCamera;
};
