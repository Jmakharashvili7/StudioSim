#pragma once
#include "Actor.h"

class Character : public Actor
{
public:
	Character(std::string name, GameObjectData* data, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData, const PhysicsData& physicsData, const MovementData& movementData, const AnimationData& animationData);
	~Character();

public:
	// Collision
	virtual void AddCollision(GameObject* collidingObject, const std::map<CollisionSide, bool>& collidingSides) override;
	virtual void RemoveCollision(GameObject* gameObject) override;

	// Jumping
	void Jump();
	virtual inline void SetJumping(const bool bjumping) { m_bjumping = bjumping; }
	virtual inline const bool GetJumping() const { return m_bjumping; }
	virtual inline const float GetJumpHeight() const { return m_movementData.jumpHeight; }
	virtual inline void SetCurrentJumpForce(const float inJumpForce) { m_currentJumpForce = inJumpForce; }
	virtual inline const float GetCurrentJumpForce() const { return m_currentJumpForce; }

protected:
	// Movement
	MovementData m_movementData = MovementData();
	bool m_bjumping = false;
	float m_currentJumpForce = 0.0f;
};

