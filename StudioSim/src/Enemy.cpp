#include "pch.h"

#include "Enemy.h"
#include "AIComponent.h"
#include "Quack.h"

Enemy::Enemy(std::string name, VertexData* data, const TransformData& transformData, const CollisionData& collisionData, const std::string& textureName, const PhysicsData& physicsData, const MovementData& movementData, const EntityData& entityData, const AnimationData& animationData) 
	: Character{ name, data, transformData, collisionData, textureName, physicsData, movementData, entityData, animationData }
{
	m_type = GameObjectType::ENEMY;

	// AI init
	m_aiComponent = new AIComponent(this, 2, Quack::GetGrid());
	AddComponent(m_aiComponent);
}

Enemy::~Enemy()
{
}

void Enemy::Update(const float deltaTime)
{
	Character::Update(deltaTime);
}

void Enemy::AddCollision(GameObject* collidingObject)
{
	Character::AddCollision(collidingObject);
}

void Enemy::RemoveCollision(GameObject* gameObject)
{
	Character::RemoveCollision(gameObject);
}
