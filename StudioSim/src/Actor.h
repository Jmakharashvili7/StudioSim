#pragma once
#include "GameObject.h"
#include "BasicIncludes.h"

class Actor : public GameObject
{
public:
	Actor(GameObjectData* data, const TextureData& textureData, const PhysicsData& physicsData);
	~Actor();

	void Jump();

	// Setters
	inline void SetJumping(const bool bjumping) { m_bjumping = bjumping; }
	inline void SetCurrentJumpForce(const float inJumpForce) { m_currentJumpForce = inJumpForce; }

	// Getters
	inline const bool GetSimulatingGravity() const { return m_bsimulateGravity; }
	inline const float GetMass() const { return m_mass; }
	inline const float GetJumpHeight() const { return m_jumpHeight; }

	inline const bool GetJumping() const { return m_bjumping; }
	inline const float GetCurrentJumpForce() const { return m_currentJumpForce; }

private:
	/* Physics */
	// Settings
	bool m_bsimulateGravity = false;
	float m_mass = 10.0f;
	float m_jumpHeight = 50.0f;

	// Variables
	bool m_bjumping = false;
	float m_currentJumpForce = 0.0f;
};

