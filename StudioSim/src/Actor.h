#pragma once
#include "GameObject.h"
#include "BasicIncludes.h"

class Animate;
class InputComponent;
class Component;

class Actor : public GameObject
{
public:
	Actor(std::string name, VertexData* data, const TransformData& transformData, const CollisionData& collisionData, const std::string& textureName, const PhysicsData& physicsData, const AnimationData& animationData);
	virtual ~Actor();

	// Rendering
	virtual void Draw(Shader* mainShader) override;

	// Update
	virtual void Update(const float deltaTime) override;

	// Physics
	virtual inline const bool GetSimulatingGravity() const { return m_physicsData.bsimulateGravity; }
	virtual inline const float GetMass() const { return m_physicsData.mass; }
	inline PhysicsData GetPhysicsData() { return m_physicsData; }
	inline void SetMass(float newMass) { m_physicsData.mass = newMass; }
	inline void SetSimulateGravity(bool gravityStatus) { m_physicsData.bsimulateGravity = gravityStatus; }

	// Animation
	virtual inline Animate* const GetAnimator() { return m_animator; }
	inline AnimationData GetAnimationData() { return m_animationData; }

	// Collision
	virtual void AddCollision(GameObject* collidingObject);
	virtual void RemoveCollision(GameObject* gameObject);
	virtual inline void SetCollidingWithGround(const bool bcollidingWithGround) { m_bcollidingWithGround = bcollidingWithGround; }
	virtual inline const bool const GetCollidingWithGround() { return m_bcollidingWithGround; }

	// Components
	virtual void AddComponent(Component* component);
	virtual void ClearComponents();
	virtual void ReorderComponents(); //TODO

	inline virtual std::vector<Component*> GetComoponents() { return m_components; }

	// Input
	virtual inline InputComponent* const GetInputComponent() { return m_inputComponent; }

	inline bool GetAnimationStatus() { return m_banimated; }
	inline void SetAnimationStatus(bool animated) { m_banimated = animated; }

protected:
	// Animation
	Animate* m_animator = nullptr;
	bool m_banimated = false;
	AnimationData m_animationData;

	// Physics
	PhysicsData m_physicsData = PhysicsData();

	// Collision
	bool m_bcollidingWithGround = false;

	// Components
	std::vector<Component*> m_components;

	// Input
	InputComponent* m_inputComponent = nullptr;
};

