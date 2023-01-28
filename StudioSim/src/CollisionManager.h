#pragma once
#include "BasicIncludes.h"
#include "QuackPhysics.h"
#include "Actor.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Update(const float deltaTime);

	inline void AddGameObject(GameObject* inGameObject) { m_gameObjects.push_back(inGameObject); }
	void RemoveGameObject(GameObject* gameObjectToRemove);
private:
	std::vector<GameObject*> m_gameObjects;
};

