#include "Actor.h"
#include "Animate.h"
#include "Quack.h"

Actor::Actor(std::string name, GameObjectData* data, const TransformData& transformData, const TextureData& textureData, const PhysicsData& physicsData, const AnimationData& animationData) 
	: GameObject{name, data, transformData, textureData }
{
	// Physics init
	m_bsimulateGravity = physicsData.bsimulateGravity;
	m_mass = physicsData.mass;
	m_jumpHeight = physicsData.jumpHeight;

	//Animation init
	m_banimated = animationData.banimated;
	if (m_banimated)
	{
		m_animator = new Animate(this, animationData.rows, animationData.columns);
	}
	m_Input = new InputComponent(this, 2, Quack::GetWindow()->GetGLFWWindow());
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

void Actor::Draw(Shader* mainShader)
{
	if (m_animator)
	{
		m_animator->UpdateTextCoord(Quack::GetDeltaTime());
	}

	GameObject::Draw(mainShader);
}

void Actor::Update(float deltaTime)
{

	GameObject::Update(deltaTime);
	//m_Input->Update(deltaTime);
	
}

void Actor::AddImpulseForce(Vector3 force)
{
	if (m_bsimulateGravity && !m_bimpulseActive)
	{
		m_bimpulseActive = true;
		m_currentImpulseForce = force;
		m_testImpulseForceMag = force;
	}
}
