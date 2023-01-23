#pragma once
#include "BasicIncludes.h"
#include "GameObject.h"
#include "QuackPhysics.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	static void Update(const float deltaTime);

	inline static void AddGameObject(GameObject* inGameObject) { m_gameObjects.push_back(inGameObject); }

private:
	static std::vector<GameObject*> m_gameObjects;
	static QuackPhysics* m_quackPhysics;
};

