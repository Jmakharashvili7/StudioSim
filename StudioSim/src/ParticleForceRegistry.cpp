#include "ParticleForceRegistry.h"
#include "Actor.h"
#include "Component.h"

ParticleForceRegistry::ParticleForceRegistry()
{
}

ParticleForceRegistry::~ParticleForceRegistry()
{
}

void ParticleForceRegistry::Add(ParticlePhysicsComponent* particle, ParticleForceGenerator* forceGen)
{
	ParticleForceRegistration newRegistration{ particle, forceGen };
	registrations.push_back(newRegistration);
}

void ParticleForceRegistry::Remove(ParticlePhysicsComponent* particle, ParticleForceGenerator* forceGen)
{
	ParticleForceRegistration newRegistration{ particle, forceGen };
	int index = 0;
	for (ParticleForceRegistration particleRegister : registrations)
	{
		if (particleRegister.particle == newRegistration.particle && particleRegister.forceGen == newRegistration.forceGen)
		{
			registrations.erase(registrations.begin() + index);
		}
		index++;
	}
}

void ParticleForceRegistry::Clear()
{
	registrations.clear();
}

void ParticleForceRegistry::UpdateForces(float deltaTime)
{
	Registry::iterator i = registrations.begin();
	for (; i != registrations.end(); i++)
	{
		i->forceGen->UpdateForce(i->particle, deltaTime);
	}
}
