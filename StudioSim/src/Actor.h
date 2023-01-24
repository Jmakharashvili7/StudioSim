#pragma once
#include "GameObject.h"
#include "BasicIncludes.h"

class Animate;
class InputComponent;
class Component;

class Actor : public GameObject
{
public:
	Actor(std::string name, GameObjectData* data, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData, const PhysicsData& physicsData, const AnimationData& animationData);
	~Actor();

	// Rendering
	virtual void Draw(Shader* mainShader) override;

	// Update
	virtual void Update(const float deltaTime) override;

	// Physics
	void Jump();
	inline void SetJumping(const bool bjumping) { m_bjumping = bjumping; }
	inline const bool GetJumping() const { return m_bjumping; }
	inline const float GetJumpHeight() const { return m_physicsData.jumpHeight; }
	inline void SetCurrentJumpForce(const float inJumpForce) { m_currentJumpForce = inJumpForce; }
	inline const float GetCurrentJumpForce() const { return m_currentJumpForce; }
	inline const bool GetSimulatingGravity() const { return m_physicsData.bsimulateGravity; }
	inline const float GetMass() const { return m_physicsData.mass; }

	// Animation
	inline Animate* const GetAnimator() { return m_animator; }

	// Collision
	virtual void AddCollision(GameObject* collidingObject, const std::map<CollisionSide, bool>& collidingSides) override;
	virtual void RemoveCollision(GameObject* gameObject) override;
	inline void SetCollidingWithGround(const bool bcollidingWithGround) { m_bcollidingWithGround = bcollidingWithGround; }
	const bool const GetCollidingWithGround();

	// Components
	void AddComponent(Component* component);
	void ClearComponents();
	void ReorderComponents(); //TODO

	// Input
	inline InputComponent* const GetInputComponent() { return m_inputComponent; }

	//TEST
	void AddImpulseForce(Vector3 force);
	inline const bool GetImpulseActive() const { return m_bimpulseActive; }
	inline void SetImpulseActive(const bool bimpulseActive) { m_bimpulseActive = bimpulseActive; }
	inline void SetCurrentImpulseForce(const Vector3 inImpulseForce) { m_currentImpulseForce = inImpulseForce; }
	inline const Vector3 const GetCurrentImpulseForce() { return m_currentImpulseForce; }
	inline const Vector3 const GetImpulseForceMag() { return m_testImpulseForceMag; }


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

	// Components
	std::vector<Component*> m_components;

	// Input
	InputComponent* m_inputComponent = nullptr;

	//TEST
	bool m_bimpulseActive = false;
	Vector3 m_testImpulseForceMag = Vector3(0.0, 3.0f, 0.0f);
	Vector3 m_currentImpulseForce = Vector3::Zero;
};

