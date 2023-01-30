#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(Actor* owner, int updateOrder, const float mass, const bool bSimulateGravity) : Component(owner, updateOrder), m_InverseMass(1 / mass), m_bSimulateGravity(bSimulateGravity)
{	
	m_Gravity = Vector3(0, -m_GravitationalValue, 0);
	m_Acceleration = m_InverseMass * (1 / m_InverseMass) * m_Gravity;
	m_Dampening = 0.995f;
	m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
	m_Force = Vector3(0.0f, 0.0f, 0.0f);
	m_owningActor = owner;
	m_updateOrder = updateOrder;
}


PhysicsComponent::~PhysicsComponent()
{

}

void PhysicsComponent::Update(float deltaTime)
{

	if (m_InverseMass <= 0.0f || m_bOnGround || !m_bSimulateGravity) return;

	m_owningActor->AdjustPosition(m_Velocity * deltaTime);
	
	Vector3 resultingAcc = m_Acceleration;
	resultingAcc += m_Force * m_InverseMass;

	m_Velocity += resultingAcc * deltaTime;

	m_Velocity *= powf(m_Dampening, deltaTime);
	
	ClearAccumulator();
}

void PhysicsComponent::UpdateAccelerationByGravity()
{
	m_Gravity = Vector3(0, -m_GravitationalValue, 0);
	m_Acceleration = m_InverseMass * (1 / m_InverseMass) * m_Gravity;
}

void PhysicsComponent::ClearAccumulator()
{
	m_Force.Clear();
}

void PhysicsComponent::AddForce(const Vector3& force)
{
	cout << m_Force.x << "  " << m_Force.y << "  " << m_Force.z << endl;
	if (m_bOnGround)
	{
		m_bOnGround = !m_bOnGround;
	}
	m_Force += force;
}

void PhysicsComponent::SetOnGround(const bool bOnGround)
{
	m_bOnGround = bOnGround;

	if (bOnGround)
	{
		ResetForces();
	}
	else
	{
		UpdateAccelerationByGravity();
	}
}

void PhysicsComponent::SetSimulateGravity(const bool bSimulateGravity)
{
	m_bSimulateGravity = bSimulateGravity;
	
	if (!bSimulateGravity)
	{
		ResetForces();
	}
	else
	{
		UpdateAccelerationByGravity();
	}
}

void PhysicsComponent::ResetForces()
{
	//SetAcceleration(Vector3(0, 0, 0));
	SetVelocity(Vector3(0, 0, 0));
}
