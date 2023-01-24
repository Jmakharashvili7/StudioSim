#pragma once
#include "GameObject.h"
#include "BasicIncludes.h"

class Animate;

class Actor : public GameObject
{
public:
	Actor(std::string name, GameObjectData* data, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData, const PhysicsData& physicsData, const AnimationData& animationData);
	~Actor();

	// Rendering
	virtual void Draw(Shader* mainShader) override;

	// Physics
	void Jump();
	inline void SetJumping(const bool bjumping) { m_bjumping = bjumping; }
	inline const bool GetJumping() const { return m_bjumping; }
	inline const float GetJumpHeight() const { return m_physicsData.jumpHeight; }
	inline void SetCurrentJumpForce(const float inJumpForce) { m_currentJumpForce = inJumpForce; }
	inline const float GetCurrentJumpForce() const { return m_currentJumpForce; }
	inline const bool GetSimulatingGravity() const { return m_physicsData.bsimulateGravity; }
	inline const float GetMass() const { return m_physicsData.mass; }
	inline  void SetMass(float mass) { m_physicsData.mass = mass; }

	// Animation
	inline Animate* const GetAnimator() { return m_animator; }

	// Collision
	virtual void AddCollision(GameObject* collidingObject) override;
	virtual void RemoveCollision(GameObject* gameObject) override;
	inline void SetCollidingWithGround(const bool bcollidingWithGround) { m_bcollidingWithGround = bcollidingWithGround; }
	const bool const GetCollidingWithGround();

	//TEST
	void AddImpulseForce(Vector3 force);
	inline const bool GetImpulseActive() const { return m_bimpulseActive; }
	inline void SetImpulseActive(const bool bimpulseActive) { m_bimpulseActive = bimpulseActive; }
	inline void SetCurrentImpulseForce(const Vector3 inImpulseForce) { m_currentImpulseForce = inImpulseForce; }
	inline const Vector3 const GetCurrentImpulseForce() { return m_currentImpulseForce; }
	inline const Vector3 const GetImpulseForceMag() { return m_testImpulseForceMag; }

	//Physics
	void Update(float deltatime);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void moveConstVelocity(Vector3 velocity, float deltaTime);
	void moveConstAcceleration(Vector3 acceleration, float deltaTime);

	float GetWeight() { return m_weight; }
	Vector3 GetThrustForce() { return m_thrustForce; }
	Vector3 GetBrakeForce() { return m_brakeForce; }
	Vector3 GetGravityForce() { return m_gravityForce; }
	Vector3 GetAcceleration() { return m_acceleration; }
	Vector3 GetVelocity() { return m_velocity; }
	Vector3 GetNetForce() { return m_netForce; }


	void SetThrustForce(Vector3 tForce) { m_thrustForce = tForce; }
	void SetBrakeForce(Vector3 bForce) { m_brakeForce = bForce; }
	void SetGravityForce(Vector3 gForce) { m_gravityForce = gForce; }
	void SetVelocity(Vector3 velocity) { m_velocity = velocity; }
	void SetAcceleration(Vector3 acceleration) { m_acceleration = acceleration; }
	void Reset();

	void UpdateNetForce();
	void UpdateAcceleration();



private:
	// Animation
	Animate* m_animator = nullptr;
	bool m_banimated = false;

	// Physics
	PhysicsData m_physicsData = PhysicsData();

	bool m_bjumping = false;
	float m_currentJumpForce = 0.0f;

	// Collision
	bool m_bcollidingWithGround = false;

	//TEST
	bool m_bimpulseActive = false;
	Vector3 m_testImpulseForceMag = Vector3(0.0, 3.0f, 0.0f);
	Vector3 m_currentImpulseForce = Vector3::Zero;

	//Physics variables
	Vector3 m_velocity;
	Vector3 m_acceleration;
	Vector3 m_netForce;
	Vector3 m_thrustForce;
	Vector3 m_brakeForce;
	Vector3 m_gravityForce;
	float m_weight;
	float _decelRate = 2.0f;
};

