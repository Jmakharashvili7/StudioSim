#pragma once
#include "ParticlePhysicsComponent.h"
#include "ParticleForceGenerator.h"


class ParticleForceRegistry
{
public:
	ParticleForceRegistry();
	~ParticleForceRegistry();

	/// <summary>
	/// Registers the given force to apply to the given particle
	/// </summary>
	/// <param name="particle"></param>
	/// <param name="forceGen"></param>
	void Add(ParticlePhysicsComponent* particle, ParticleForceGenerator* forceGen);

	/// <summary>
	/// Removes the given registered pair from the registry. If the pair is not registered this method will have no effect
	/// </summary>
	/// <param name="particle"></param>
	/// <param name="forceGen"></param>
	void Remove(ParticlePhysicsComponent* particle, ParticleForceGenerator* forceGen);

	/// <summary>
	/// Clears all registrations from the registry. This will not delete the partticles or the force generators themselves, just the records of their connection
	/// </summary>
	void Clear();

	/// <summary>
	/// Calls all the force generators to update forces of their corresponding particles
	/// </summary>
	/// <param name="deltaTime"></param>
	void UpdateForces(float deltaTime);


protected:
/// <summary>
/// keeps track of one generator and the particle it applies to
/// </summary>
	struct ParticleForceRegistration
	{
		ParticlePhysicsComponent* particle;
		ParticleForceGenerator* forceGen;
	};
	/// <summary>
	/// holds the list of registrations
	/// </summary>
	typedef vector<ParticleForceRegistration> Registry;
	Registry registrations;



private:

};



