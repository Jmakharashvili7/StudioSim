#include "ParticlePhysics.h"

ParticlePhysics::ParticlePhysics(class Actor* owner, int updateOrder,Transform* transform) : Component( owner,  updateOrder)
{
	m_Transform = transform;

	m_Gravity = Vector3(0, -4.0f, 0);
	m_Position = transform->GetPosition();
	SetMass(2.0f);
	m_Acceleration = m_InverseMass * (1 / m_InverseMass) * m_Gravity;
	m_Dampening = 0.995f;
	m_Velocity = Vector3(-3.0f, 0.0f, 0.0f);
	
	m_Force = Vector3(0.0f, 0.0f, 0.0f);
	m_Owner = owner;
	m_UpdateOrder = updateOrder;
}


ParticlePhysics::~ParticlePhysics()
{

}

void ParticlePhysics::Update(float deltaTime)
{
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

void ParticlePhysics::ClearAccumulator()
{
	m_Force.Clear();
}
