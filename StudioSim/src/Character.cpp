#include "Character.h"

Character::Character(std::string name, GameObjectData* data, const TransformData& transformData, const CollisionData& collisionData, 
	const TextureData& textureData, const PhysicsData& physicsData, const MovementData& movementData, const AnimationData& animationData)
	: Actor {name, data, transformData, collisionData, textureData, physicsData, animationData}, m_movementData(movementData)
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
