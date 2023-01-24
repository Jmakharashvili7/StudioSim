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
class GameTimer;
class UILayer;
class Window;

struct SceneInfo
{
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
private:
	void SetupShaders();
	void HandleLights();

	void HandleInput();

	void Update();
	void PhysicsUpdate();

	GameObject* LoadGameObject(std::string path);
	bool StoreGameObject(GameObject* gameObject, int index);
private:
	std::string m_name;

	std::vector<GameObject*> m_gameObjects;
	std::vector<Actor*> m_gameActors;
	Grid<PathNode> m_grid;

	// windows
	UILayer* m_uiMain;
	Window* m_window;

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

	GameTimer m_gameTimer;

	Actor* m_duck;
	GameObject* m_ground;
	GameObject* m_testSprite;

	PhysicsManager* m_physicsManager;
	CollisionManager* m_collisionManager;
};

