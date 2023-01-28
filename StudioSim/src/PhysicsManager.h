#pragma once
#include "BasicIncludes.h"
#include "Character.h"
#include "CollisionManager.h"

#define GFORCE 9.81

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void Update(const float deltaTime);

	inline void AddGameActor(Actor* inGameActor) { m_gameActors.push_back(inGameActor); }
	void RemoveGameActor(Actor* actorToRemove);
private:
	std::vector<Actor*> m_gameActors;
};

