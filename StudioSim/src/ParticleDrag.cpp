#include "ParticleDrag.h"
#include "ParticlePhysicsComponent.h"

ParticleDrag::ParticleDrag(float drag, float dragSquared)
{
	m_drag = drag;
	m_dragSquared = dragSquared;
}

void ParticleDrag::UpdateForce(ParticlePhysicsComponent* particle, float deltaTime)
{
	Vector3 force = particle->GetVelocity();

	float dragCoeff = force.Length();
	dragCoeff = m_drag * dragCoeff + m_dragSquared * dragCoeff;

	//calculate the final force and apply it
	force.Normalize();
	force *= -dragCoeff;
	particle->AddForce(force);
	
}
