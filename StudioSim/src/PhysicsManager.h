#pragma once
#include "BasicIncludes.h"
#include "Character.h"

#define GFORCE 9.81

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	static void Update(const float deltaTime);

	inline static void AddGameActor(Actor* inGameActor) { m_gameActors.push_back(inGameActor); }

private:
	static std::vector<Actor*> m_gameActors;
};

