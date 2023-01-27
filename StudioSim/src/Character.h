#pragma once
#include "Actor.h"

class Character : public Actor
{
public:
	Character(std::string name, GameObjectData* data, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData, const PhysicsData& physicsData, const MovementData& movementData, const EntityData& entityData, const AnimationData& animationData);
	virtual ~Character();

public:
	// Collision
	virtual void AddCollision(GameObject* collidingObject) override;
	virtual void RemoveCollision(GameObject* gameObject) override;

	// Jumping
	void Jump();
	virtual inline void SetJumping(const bool bjumping) { m_bjumping = bjumping; }
	virtual inline const bool GetJumping() const { return m_bjumping; }
	virtual inline const float GetJumpHeight() const { return m_movementData.jumpHeight; }
	virtual inline void SetCurrentJumpForce(const float inJumpForce) { m_currentJumpForce = inJumpForce; }
	virtual inline const float GetCurrentJumpForce() const { return m_currentJumpForce; }

	// Movement
	virtual inline float GetMovementSpeed() const { return m_movementData.movementSpeed; }
	inline MovementData GetMovementData() { return m_movementData; }

	// Health
	virtual void TakeDamage(const float amount);
	virtual void Kill();
	virtual void Die();
	virtual void SetHealth(const float inHealth);
	virtual void AdjustHealth(const float adjustAmount);
	virtual const inline float GetHealth() const { return m_entityData.health; }
	virtual void CheckShouldDie();

	// Entity
	inline EntityData GetEntityData() { return m_entityData; }

protected:
	// Movement
	MovementData m_movementData = MovementData();
	bool m_bjumping = false;
	float m_currentJumpForce = 0.0f;

	// Entity
	EntityData m_entityData = EntityData();
};

