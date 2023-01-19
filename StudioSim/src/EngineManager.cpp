#include "EngineManager.h"

GameTimer* EngineManager::m_gameTimer;
std::vector<GameObject*> EngineManager::m_gameObjects;

GameObject* EngineManager::GetGameObject(std::string name)
{
	for (GameObject* gameObject : m_gameObjects)
	{
		if (name == gameObject->GetName())
		{
			return gameObject;
		}
	}
}
