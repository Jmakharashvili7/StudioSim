#include "pch.h"

#include "Character.h"
#include "Quack.h"
#include "PhysicsComponent.h"

Character::Character(std::string name, VertexData* data, const TransformData& transformData, const CollisionData& collisionData, 
	const std::string& textureName, const PhysicsData& physicsData, const MovementData& movementData, const EntityData& entityData, const AnimationData& animationData)
	: Actor {name, data, transformData, collisionData, textureName, physicsData, animationData}, m_movementData(movementData), m_entityData(entityData)
{
	m_type = GameObjectType::CHARACTER;

	// Health init
	ResetCurrentHealth();
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

		if (m_physicsComponent)
		{
			m_physicsComponent->AddForce(Vector3(0.0f, m_movementData.jumpHeight, 0.0f));
		}
	}
}

void Character::SetCurrentHealth(const float inHealth)
{
	m_currentHealth = inHealth;
	CheckShouldDie();
}

void Character::AdjustCurrentHealth(const float adjustAmount)
{
	m_currentHealth += adjustAmount;
	CheckShouldDie();
}

void Character::CheckShouldDie()
{
	if (GetCurrentHealth() <= 0.0f)
	{
		Die();
	}
}

void Character::SetMaxHealth(const float newMaxHealth, const bool bUpdateHealth)
{
	m_entityData.maxHealth = newMaxHealth;

	if (bUpdateHealth)
	{
		SetCurrentHealth(newMaxHealth);
	}
}

void Character::TakeDamage(const float amount)
{
	std::cout << "Ouch - " + m_name << std::endl;
	AdjustCurrentHealth(amount);
}

void Character::Kill()
{
	SetCurrentHealth(0.0f);
}

void Character::Die()
{
	std::cout << "Im dead - " + m_name << std::endl;
}
