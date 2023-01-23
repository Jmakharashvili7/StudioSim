#include "Actor.h"
#include "Animate.h"
#include "Quack.h"

Actor::Actor(GameObjectData* data, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData, const PhysicsData& physicsData, const AnimationData& animationData)
	: GameObject{ data, transformData, collisionData, textureData }, m_physicsData(physicsData)
{
	//Animation init
	m_banimated = animationData.banimated;
	if (m_banimated)
	{
		m_animator = new Animate(this, animationData.rows, animationData.columns);
	}
}

Actor::~Actor()
{

}

void Actor::Jump()
{
	if (m_physicsData.bsimulateGravity && !m_bjumping)
	{
		m_bjumping = true;
		m_currentJumpForce = m_physicsData.jumpHeight;
	}
}

void Actor::Draw(Shader* mainShader)
{
	if (m_animator)
	{
		m_animator->UpdateTextCoord(Quack::GetDeltaTime());
	}

	GameObject::Draw(mainShader);
}

bool const Actor::GetCollidingWithGround()
{
	return m_bcollidingWithGround;
}

void Actor::AddImpulseForce(glm::vec3 force)
{
	if (m_physicsData.bsimulateGravity && !m_bimpulseActive)
	{
		m_bimpulseActive = true;
		m_currentImpulseForce = force;
		m_testImpulseForceMag = force;
	}
}
