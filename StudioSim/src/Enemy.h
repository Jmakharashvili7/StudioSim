#pragma once
#include "Character.h"

class AIComponent;

class Enemy : public Character
{
public:
	Enemy(std::string name, VertexData* data, const TransformData& transformData, const CollisionData& collisionData, const std::string& textureName, const PhysicsData& physicsData, const MovementData& movementData, const EntityData& entityData, const AnimationData& animationData);
	virtual ~Enemy();

	// Update
	virtual void Update(const float deltaTime) override;

	// Collision
	virtual void AddCollision(GameObject* collidingObject) override;
	virtual void RemoveCollision(GameObject* gameObject) override;

protected:
	// AI
	AIComponent* m_aiComponent = nullptr;
};

