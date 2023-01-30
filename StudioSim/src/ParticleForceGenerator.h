#pragma once
class ParticleForceGenerator
{
public:
	/// <summary>
	/// Overload this in implementations of the interface to calculate and update the force applied to the given particle
	/// </summary>
	virtual void UpdateForce(class ParticlePhysicsComponent* particle, float deltaTime) = 0;
	//virtual void UpdateForce(class Actor* particle, float deltaTime) = 0;
};

