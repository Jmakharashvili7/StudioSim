#include "Character.h"
#include "Quack.h"

Character::Character(std::string name, GameObjectData* data, const TransformData& transformData, const CollisionData& collisionData, 
	const TextureData& textureData, const PhysicsData& physicsData, const MovementData& movementData, const EntityData& entityData, const AnimationData& animationData)
	: Actor {name, data, transformData, collisionData, textureData, physicsData, animationData}, m_movementData(movementData), m_entityData(entityData)
{

}

Character::~Character()
{

}

void Character::AddCollision(GameObject* collidingObject, const std::map<CollisionSide, bool>& collidingSides)
{
	if (collidingObject->GetName() == "ground")
	{
		SetJumping(false); 
		SetCurrentJumpForce(0.0f);
		SetCollidingWithGround(true);
	}

	Actor::AddCollision(collidingObject, collidingSides);
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

void Character::Destroy()
{
	Actor::Destroy();
}

void Character::TakeDamage(const float amount)
{
	std::cout << "Ouch" << std::endl;
	AdjustHealth(amount);
}

void Character::Kill()
{
	SetHealth(0.0f);
}

void Character::Die()
{
	std::cout << "Im dead" << std::endl;
	Destroy();
}
