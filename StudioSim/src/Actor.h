#pragma once
#include "GameObject.h"
#include "BasicIncludes.h"

class Animate;

class Actor : public GameObject
{
public:
	Actor(std::string name, GameObjectData* data, const TransformData& transformData, const TextureData& textureData, const PhysicsData& physicsData, const AnimationData& animationData);
	~Actor();

	void Jump();

	virtual void Draw(Shader* mainShader) override;
	

	// Setters
	inline void SetJumping(const bool bjumping) { m_bjumping = bjumping; }
	inline void SetCurrentJumpForce(const float inJumpForce) { m_currentJumpForce = inJumpForce; }

	// Getters
	inline const bool GetSimulatingGravity() const { return m_bsimulateGravity; }
	inline const float GetMass() const { return m_mass; }
	inline const float GetJumpHeight() const { return m_jumpHeight; }

	inline const bool GetJumping() const { return m_bjumping; }
	inline const float GetCurrentJumpForce() const { return m_currentJumpForce; }

	inline Animate* const GetAnimator() { return m_animator; }

	//TEST
	void AddImpulseForce(glm::vec3 force);
	inline const bool GetImpulseActive() const { return m_bimpulseActive; }
	inline void SetImpulseActive(const bool bimpulseActive) { m_bimpulseActive = bimpulseActive; }
	inline void SetCurrentImpulseForce(const glm::vec3 inImpulseForce) { m_currentImpulseForce = inImpulseForce; }
	inline const glm::vec3 const GetCurrentImpulseForce() { return m_currentImpulseForce; }
	inline const glm::vec3 const GetImpulseForceMag() { return m_testImpulseForceMag; }

	//Physics
	void Update(float deltatime);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void moveConstVelocity(glm::vec3 velocity, float deltaTime);
	void moveConstAcceleration(glm::vec3 acceleration, float deltaTime);

	glm::vec3 GetThrustForce() { return m_thrustForce; }
	glm::vec3 GetBrakeForce() { return m_brakeForce; }
	glm::vec3 GetGravityForce() { return m_gravityForce; }
	glm::vec3 GetAcceleration() { return m_acceleration; }
	glm::vec3 GetVelocity() { return m_velocity; }
	glm::vec3 GetNetForce() { return m_netForce; }


	void SetThrustForce(glm::vec3 tForce) { m_thrustForce = tForce; }
	void SetBrakeForce(glm::vec3 bForce) { m_brakeForce = bForce; }
	void SetGravityForce(glm::vec3 gForce) { m_gravityForce = gForce; }
	void SetVelocity(glm::vec3 velocity) { m_velocity = velocity; }
	void SetAcceleration(glm::vec3 acceleration) { m_acceleration = acceleration; }
	void Reset();

	void UpdateNetForce();
	void UpdateAcceleration();

	float GetMass() { return m_mass; }
	void SetMass(float mass) { m_mass = mass; }

private:
	/* Animation */
	Animate* m_animator = nullptr;
	bool m_banimated = false;

	/* Physics */
	// Settings
	bool m_bsimulateGravity = false;
	float m_mass = 10.0f;
	float m_jumpHeight = 50.0f;

	// Variables
	bool m_bjumping = false;
	float m_currentJumpForce = 0.0f;

	//TEST
	bool m_bimpulseActive = false;
	glm::vec3 m_testImpulseForceMag = glm::vec3(0.0, 10.0f, 0.0f);
	glm::vec3 m_currentImpulseForce = glm::vec3(0.0f);

	//Physics variables
	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;
	glm::vec3 m_netForce;
	glm::vec3 m_thrustForce;
	glm::vec3 m_brakeForce;
	glm::vec3 m_gravityForce;
	float m_weight;
};

