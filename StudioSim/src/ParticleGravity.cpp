#include "ParticleGravity.h"
#include "ParticlePhysicsComponent.h"

ParticleGravity::ParticleGravity(const Vector3& gravity)
{
	m_Gravity = gravity;
}

void ParticleGravity::UpdateForce(ParticlePhysicsComponent* particle, float deltaTime)
{
	//check if the object is movable
	if (!particle->HasFiniteMass()) return;

	//apply the mass scaled force to the gravity
	particle->AddForce(m_Gravity * particle->GetMass());

}
