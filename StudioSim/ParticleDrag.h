#pragma once
#include "ParticleForceGenerator.h"
class ParticleDrag :
    public ParticleForceGenerator
{
    /// <summary>
    /// holds the velocity drag coefficient
    /// </summary>
    float m_drag;

    /// <summary>
    /// holds the velocity square drag coefficient
    /// </summary>
    float m_dragSquared;

public:
    /// <summary>
    /// creates a generator with the given coefficients
    /// </summary>
    ParticleDrag(float drag, float dragSquared);

    /// <summary>
    /// Applies the drag force to the given particle
    /// </summary>
    virtual void UpdateForce(class ParticlePhysicsComponent* particle, float deltaTime);

};

