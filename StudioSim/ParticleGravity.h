#pragma once
#include "ParticleForceGenerator.h"
#include "BasicIncludes.h"

/// <summary>
///  A force generator that applies a gravitational force. One instance can be used for multiple particles.
/// </summary>
class ParticleGravity :
    public ParticleForceGenerator
{
    /// <summary>
    /// Holds the acceleration due to gravity
    /// </summary>
    Vector3 m_Gravity;

public:
    /// <summary>
    /// Creates the generator with the given acceleration
    /// </summary>
    /// <param name="gravity"></param>
    ParticleGravity(const Vector3& gravity);

    /// <summary>
    /// Applies the gravitational force to the given particle.
    /// </summary>
    /// <param name="particle"></param>
    /// <param name="deltaTime"></param>
    virtual void UpdateForce(class ParticlePhysicsComponent* particle, float deltaTime);

};

