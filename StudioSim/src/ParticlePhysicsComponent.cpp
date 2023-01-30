#include "ParticlePhysicsComponent.h"

ParticlePhysicsComponent::ParticlePhysicsComponent( Actor* owner, int updateOrder) : Component(owner, updateOrder)
{	
	
	m_Transform = owner->GetTransform();
	m_Gravity = Vector3(0, -m_GravitationalValue, 0);
	m_Position = m_Transform->GetPosition();
	SetMass(2.0f);
	m_Acceleration = m_InverseMass * (1 / m_InverseMass) * m_Gravity;
	m_Dampening = 0.995f;
	m_Velocity = Vector3(0.0f, 0.0f, 0.0f);

	m_Force = Vector3(0.0f, 0.0f, 0.0f);
	m_owningActor = owner;
	m_updateOrder = updateOrder;
	
}


ParticlePhysicsComponent::~ParticlePhysicsComponent()
{

}

void ParticlePhysicsComponent::Update(float deltaTime)
{
	if (m_InverseMass <= 0.0f) return;


	//m_Acceleration = m_InverseMass * (1 / m_InverseMass) * m_Gravity;
	//m_Position += m_Velocity * deltaTime + m_Acceleration * deltaTime * deltaTime * 0.5f;
	//m_Transform->SetPosition(m_Position);
	//or 

	m_Position += m_Velocity * deltaTime;

	Vector3 resultingAcc = m_Acceleration;
	resultingAcc += m_Force * m_InverseMass;

	m_Velocity += resultingAcc * deltaTime;

	m_Velocity *= powf(m_Dampening, deltaTime);
	m_Transform->SetPosition(m_Position);
	ClearAccumulator();
}

void ParticlePhysicsComponent::UpdateAccelerationByGravity()
{
	m_Gravity = Vector3(0, -m_GravitationalValue, 0);
	m_Acceleration = m_InverseMass * (1 / m_InverseMass) * m_Gravity;
}

void ParticlePhysicsComponent::ClearAccumulator()
{
	m_Force.Clear();
}

void ParticlePhysicsComponent::AddForce(const Vector3& force)
{
	m_Force += force;
}
