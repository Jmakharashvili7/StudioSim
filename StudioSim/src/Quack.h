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

class LayerStack;
class UIRenderer;
class UILayer;

#define MAX_FRAME_RATE 144
#define NUMBER_OF_SQUARES 4

class QuackPhysics;

class Quack
{
public:
	enum Facing
	{
		RIGHT,
		LEFT
	};
	static int InitEngine();

	static void Update();
	static void RenderUpdate();
	static void PhysicsUpdate();

	static void ShutDown();
	static Window* GetWindow() { return m_window; }

	static void GetFrameRate(float deltatime);

	static void ImGUIInit();

	static GameObject* CreateNewGameObject(std::string name, GameObjectData* objectData, const TransformData& transformData, const TextureData& textureData);
	static Actor* CreateNewActor(std::string name, GameObjectData* objectData, const TransformData& transformData, const TextureData& textureData, const PhysicsData& physicsData, const AnimationData& animationData);

	static void Projectile(float force);
	static void ProjectileDecrement(Facing direction);

	static inline float GetDeltaTime() { return m_gameTimer.GetDeltaTime(); }
	static FrameBuffer* GetFrameBuffer() { return m_frameBuffer; }
	static UILayer* GetUILayer() { return m_uiMain; }

	//static BoundingBox CreateBoundingBox(glm::vec3 positions,glm::vec3 scale);
private:
	Quack();
	~Quack();

	static void HandleInput();
	static void InitObjects();
	static void SetupShaders();
public:
	static bool m_capFrames;
	static bool s_running;
	static bool s_glfwInitialised;
private:
	static Window* m_window;
	static LayerStack* m_layerStack;
	static UILayer* m_uiMain;
	static PhysicsManager* m_physicsManager;

	//Frame related variables
	static double m_currentTime;
	static double m_lastTime;
	static double m_deltaTime;
	static double m_frameTime;
	static double m_frameDelay;

	static GameTimer m_gameTimer;

	static int m_frameCounter;
	static int m_currentFrameRate;

	static bool m_jumping;
	static float m_jump_force;
	static bool m_thrown;
	static float m_throw_force;
	static Facing m_direction;
	static float m_rotation;
	static float m_projectileForce;

	static FrameBuffer* m_frameBuffer;

	static Actor* m_duck;
	static GameObject* m_ground;
	static GameObject* m_testSprite;

	int spTest = 0;
	static std::vector<GameObject*> m_gameObjects;
	static std::vector<Actor*> m_gameActors;


	static VertexArray* m_squareVAO;
	static glm::vec4 m_objColor;

	static glm::vec3 squarePositionData[];
	static glm::vec3 squareScaleData[];


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

	static Shader* m_mainShader;
	static Shader* m_3dShader;
	static OrthographicCamera* m_mainCamera;
};
