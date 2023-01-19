#pragma once
#include "BasicIncludes.h"
#include "Quack.h"

// Helper class to get reference to objects
class EngineManager
{
public:
	static GameTimer* GetGameTimer() { return m_gameTimer; }
	static std::vector<GameObject*> GetGameObjects() { return m_gameObjects; }
	static void SetGameObjects(std::vector<GameObject*> gameObjects) { m_gameObjects = gameObjects; }
	static GameObject* GetGameObject(std::string name);
private:
	static GameTimer* m_gameTimer;
	static std::vector<GameObject*> m_gameObjects;
private:
	EngineManager();
	~EngineManager();
};

