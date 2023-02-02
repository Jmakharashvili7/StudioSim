#include "pch.h"

#include "EngineManager.h"

GameTimer* EngineManager::m_gameTimer;
std::vector<GameObject*> EngineManager::m_gameObjects;
Character* EngineManager::m_inputCharacter;

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

GameObject* EngineManager::GetGameObject(const int index)
{
	return m_gameObjects[index];
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

int EngineManager::GetGameObjectIndex(GameObject* gameObject)
{
	int i = 0;

	for (GameObject* loopedGameObject : Quack::GetCurrentScene()->GetGameObjects())
	{
		if (gameObject == loopedGameObject)
		{
			return i;
		}

		i++;
	}

	return -1;
}

void EngineManager::SetInputCharacter(Character* newInputCharacter)
{
	m_inputCharacter = newInputCharacter;

	for (GameObject* loopedGameObject : m_gameObjects)
	{
		Character* characterObject = dynamic_cast<Character*>(loopedGameObject);
		if (characterObject)
		{
			if (characterObject == newInputCharacter)
			{
				characterObject->SetConsumingInput(true);
			}
			else
			{
				characterObject->SetConsumingInput(false);
			}
		}
	}
}

const bool EngineManager::GetCharacterConsumingInput(Character* inputCharacter)
{
	return m_inputCharacter == inputCharacter;
}
