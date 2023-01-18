#include "Actor.h"

Actor::Actor(GameObjectData* data, const TextureData& textureData, const PhysicsData& physicsData) : GameObject{data, textureData }
{
	// Physics init
	m_bsimulateGravity = physicsData.bsimulateGravity;
	m_mass = physicsData.mass;
	m_jumpHeight = physicsData.jumpHeight;
}

Actor::~Actor()
{

}

void Actor::Jump()
{
	if (m_bsimulateGravity && !m_bjumping)
	{
		m_bjumping = true;
		m_currentJumpForce = m_jumpHeight;
	}
}

void Actor::AddImpulseForce(glm::vec3 force)
{

}
