#include "pch.h"

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

int EngineManager::GetGameObjectIndex(std::string name)
{
	int i = 0;
	for (GameObject* gameObject : m_gameObjects)
	{
		if (name == gameObject->GetName())
		{
			return i;
		}

		i++;
	}
}

int EngineManager::GetGameObjectIndex(GameObject* gameObject, std::vector<GameObject*> gameObjectArray)
{
	int i = 0;
	int indexToReturn = -1;

	for (GameObject* loopedGameObject : gameObjectArray)
	{
		if (gameObject == loopedGameObject)
		{
			indexToReturn = i;
		}

		i++;
	}

	return indexToReturn;
}
