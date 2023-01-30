#pragma once
#include "BasicIncludes.h"
#include "GameObject.h"
//#include "Quack.h"

class ParticlePhysics : Component
{
public:
	ParticlePhysics( Actor* owner, int updateOrder, Transform* transform);
	~ParticlePhysics();



	void SetMass(float mass) {  m_InverseMass = 1 / mass; }
	void SetInverseMass(float inverseMass) { m_InverseMass = inverseMass; }

	virtual void Update(float deltaTime) override;

	void ClearAccumulator();

	void SetPosition() {
		//m_Position += m_Velocity * Quack::GetDeltaTime();
		//m_Transform->SetPosition(m_Position);
	}
	
	float GetSpeed() { return  m_Velocity.Length(); }
	Vector3 GetDirection() { return Vector3::Normalize(m_Velocity); }


protected:
	/// <summary>
	/// Holds the linear position of the particle in world space
	/// </summary>
	Vector3 m_Position;

	/// <summary>
	///  Holds the linear velocity of the particle in world space
	/// </summary>
	Vector3 m_Velocity;

	/// <summary>
	///  Holds the acceleration of the particle. This value can be used to set acceleration due to gravity (its primary use) or any other constant acceleration.
	/// </summary>
	Vector3 m_Acceleration;

	/// <summary>
	///  Holds the amount of damping applied to linear motion. Damping is required to remove energy added through numerical instability in the integrator.
	/// </summary>
	float m_Dampening;

	/// <summary>
	/// Holds the inverse of the mass of the particle. It is more useful to hold the inverse mass because
	/// integration is simpler and because in real-time simulation it is more useful to have objects with
	/// infinite mass (immovable) than zero mass (completely unstable in numerical simulation).
	/// </summary>
	float m_InverseMass;

	Vector3 m_Gravity;

	Vector3 m_Force;

	float m_GravitationalValue = 9.807f;

	Transform* m_Transform;
};

