#include "pch.h"

#include "Character.h"
#include "Quack.h"

Character::Character(std::string name, VertexData* data, const TransformData& transformData, const CollisionData& collisionData, 
	const std::string& textureName, const PhysicsData& physicsData, const MovementData& movementData, const EntityData& entityData, const AnimationData& animationData)
	: Actor {name, data, transformData, collisionData, textureName, physicsData, animationData}, m_movementData(movementData), m_entityData(entityData)
{
	m_type = GameObjectType::CHARACTER;

	if (true) 
	{
		std::cout << "hello" << std::endl;
	}
}

Character::~Character()
{

}

void Character::Update(const float deltaTime)
{
	Actor::Update(deltaTime);
}

void Character::AddCollision(GameObject* collidingObject)
{
	if (collidingObject->GetName() == "ground")
	{
		SetJumping(false); 
		SetCurrentJumpForce(0.0f);
		SetCollidingWithGround(true);
	}

	Actor::AddCollision(collidingObject);
}

void Character::RemoveCollision(GameObject* gameObject)
{
	Actor::RemoveCollision(gameObject);
}

void Character::Jump()
{
	if (m_physicsData.bsimulateGravity && !m_bjumping)
	{
		m_bjumping = true;
		m_currentJumpForce = m_movementData.jumpHeight;
	}
}

void Character::SetHealth(const float inHealth)
{
	m_entityData.health = inHealth;
	CheckShouldDie();
}

void Character::AdjustHealth(const float adjustAmount)
{
	m_entityData.health += adjustAmount;
	CheckShouldDie();
}

void Character::CheckShouldDie()
{
	if (GetHealth() <= 0.0f)
	{
		Die();
	}
}

void Character::TakeDamage(const float amount)
{
	std::cout << "Ouch - " + m_name << std::endl;
	AdjustHealth(amount);
}

void Character::Kill()
{
	SetHealth(0.0f);
}

void Character::Die()
{
	std::cout << "Im dead - " + m_name << std::endl;
}
