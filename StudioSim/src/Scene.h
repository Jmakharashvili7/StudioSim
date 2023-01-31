#pragma once
#include "BasicIncludes.h"
#include "Grid.h"
#include "PathNode.h"
#include "GameTime.h"

class GameObject;
class Actor;
class Shader;
class OrthographicCamera;
class PhysicsManager;
class CollisionManager;
class UILayer;
class Window;

struct SceneInfo
{
	std::string sceneName;
	uint32_t objectCount;
};

class Scene
{
public:
	Scene() {}
	Scene(const std::string& path, UILayer* uiLayer, Window* window);
	~Scene() {}

	void Render();

	inline OrthographicCamera* GetCamera() { return m_mainCamera; }
	void CloseScene();

	inline std::vector<GameObject*> GetGameObjects() { return m_gameObjects; }
private:
	void SetupShaders();
	void HandleLights();

	void HandleInput();

	void Update();
	void PhysicsUpdate();

	void printshitt() noexcept;

	GameObject* LoadGameObject(std::string path);
	bool StoreGameObject(GameObject* gameObject, int index);
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

	Shader* m_mainShader;
	Shader* m_3dShader;
	Shader* m_primitiveShader;
	OrthographicCamera* m_mainCamera;
;
	CollisionManager* m_collisionManager;

	GameTimer m_gameTimer;

	// idk if we need this
	////Frame related variables
	//static double m_currentTime;
	//static double m_lastTime;
	//static double m_deltaTime;
	//static double m_frameTime;
	//static double m_frameDelay;
};

