#pragma once
#include "BasicIncludes.h"
#include "Grid.h"
#include "PathNode.h"
#include "GameTime.h"
#include "FrameBuffer.h"

class GameObject;
class Actor;
class Shader;
class OrthographicCamera;
class PhysicsManager;
class CollisionManager;
class UILayer;
class Window;
class HUD;

struct SceneInfo
{
	std::string sceneName;
	uint32_t objectCount;
};

class Scene
{
public:
	Scene() {}
	Scene(const std::string& path, UILayer* uiLayer, Window* window, FrameBuffer* frameBuffer);
	~Scene() {}
	
	void RenderScene();

	inline OrthographicCamera* GetCamera() { return m_activeCamera; }
	void SaveScene();
	void LoadScene();

	inline std::vector<GameObject*> GetGameObjects() { return m_gameObjects; }
	void AddGameObject(GameObject* newGameObject);
	void RemoveGameObject(GameObject* gameObject);

	inline FrameBuffer* GetFrameBuffer() { return m_frameBuffer; }

	inline bool GetStopInput() { return m_StopInput; }

	void SetGravity(const bool bactive);
	void SetInput(const bool bactive);
private:
	void HandleLights();

	void HandleInput();

	void Render();
	void Update();
	void PhysicsUpdate();
private:
	std::string m_name;

	std::vector<GameObject*> m_gameObjects;
	Grid<PathNode> m_grid;

	// windows
	UILayer* m_uiMain;
	Window* m_window;

	// Scene Info
	SceneInfo m_sceneInfo;

	//lights
	glm::vec4 m_lightPos;
	glm::vec4 m_dirAmbient;
	glm::vec4 m_dirDiffuse;
	glm::vec4 m_dirSpecular;

	glm::vec3 m_pointLightPositions;
	glm::vec4 m_pointAmbient;
	glm::vec4 m_pointDiffuse;
	glm::vec4 m_pointSpecular;

	glm::vec4 m_spotAmbient;
	glm::vec4 m_spotDiffuse;
	glm::vec4 m_spotSpecular;
	glm::vec4 m_lightAmbient;

	OrthographicCamera* m_activeCamera;
;
	CollisionManager* m_collisionManager;

	GameTimer m_gameTimer;
	
	FrameBuffer* m_frameBuffer;

	bool m_StopInput = true;

	HUD* m_HUD;

	// idk if we need this
	////Frame related variables
	//static double m_currentTime;
	//static double m_lastTime;
	//static double m_deltaTime;
	//static double m_frameTime;
	//static double m_frameDelay;
	std::vector<GameObject*> m_gameObjectsToAdd;
	std::vector<GameObject*> m_gameObjectsToRemove;
};

