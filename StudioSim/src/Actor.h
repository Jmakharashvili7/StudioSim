#pragma once
#include "GameObject.h"
#include "BasicIncludes.h"

class Animate;
class InputComponent;
class Component;
class PhysicsComponent;

class Actor : public GameObject
{
public:
	Actor(std::string name, VertexData* data, const TransformData& transformData, const CollisionData& collisionData, const std::string& textureName, const PhysicsData& physicsData, const AnimationData& animationData);
	virtual ~Actor();

	// Rendering
	virtual void Draw(OrthographicCamera* camera) override;

	// Update
	virtual void Update(const float deltaTime) override;

	// Position
	virtual void AdjustPosition(const Vector3 adjustPosition) override;

	// Physics
	virtual inline const bool GetSimulatingGravity() const { return m_physicsData.bsimulateGravity; }
	virtual inline const float GetMass() const { return m_physicsData.mass; }
	inline PhysicsData GetPhysicsData() { return m_physicsData; }
	void SetMass(float newMass);
	void SetSimulateGravity(bool gravityStatus);
	void SetGravityMultiplier(const float gravityMultiplier);
	virtual inline const float GetGravityMultiplier() const { return m_physicsData.gravityMultiplier; }

	// Animation
	virtual inline Animate* const GetAnimator() { return m_animator; }
	inline AnimationData GetAnimationData() { return m_animationData; }
	virtual void SetAnimationStatus(bool animated);
	virtual inline const bool GetAnimationStatus() { return m_animationData.banimated; }
	virtual void SetAnimationRowData(std::vector<AnimationRowData> newAnimationRowData);
	virtual inline const std::vector<AnimationRowData> GetAnimationRowData() { return m_animationData.animationRowData; }
	virtual void SetAnimationDataRowName(const AnimationRowData& animationRowData, const std::string newName);
	virtual const std::string GetAnimationDataRowName(const AnimationRowData& animationRowData);
	virtual void SetAnimationDataRowNumber(const AnimationRowData& animationRowData, const int newRowNumber);
	virtual const int GetAnimationDataRowNumber(const AnimationRowData& animationRowData);
	virtual void SetAnimationDataNumberOfColumns(const AnimationRowData& animationRowData, const int newNumberOfColumns);
	virtual const int GetAnimationDataNumberOfColumns(const AnimationRowData& animationRowData);
	virtual void SetAnimationDataPlayRate(const AnimationRowData& animationRowData, const float newPlayRate);
	virtual const float GetAnimationDataPlayRate(const AnimationRowData& animationRowData);
	virtual void SetAnimationDataTotalRows(const int newTotalRows);
	virtual inline const int GetAnimationDataTotalRows() { return m_animationData.totalRows; }
	virtual void SetAnimationDataTotalColumns(const int newTotalColumns);
	virtual inline const int GetAnimationDataTotalColumns() { return m_animationData.totalColumns; }
	virtual void AddAnimationData();
	virtual const AnimationRowData& GetAnimationByName(std::string name);
	virtual void SetCurrentAnimation(const AnimationRowData& newCurrentAnimation);

	// Collision
	virtual void AddCollision(GameObject* collidingObject);
	virtual void RemoveCollision(GameObject* gameObject);
	virtual void SetCollidingWithGround(const bool bcollidingWithGround);
	virtual inline const bool const GetCollidingWithGround() { return m_bcollidingWithGround; }

	// Components
	virtual void AddComponent(Component* component);
	virtual void ClearComponents();
	virtual void ReorderComponents(); //TODO

	template <typename T>
	T* GetComponent() {
		for (Component* c : m_components)
		{
			if (dynamic_cast<T*>(c))
			{
				return (T*)c;
			}
		}
		return nullptr;
	}

	inline virtual std::vector<Component*> GetComoponents() { return m_components; }

protected:
	// Animation
	Animate* m_animator = nullptr;
	bool m_banimated = false;
	AnimationData m_animationData = AnimationData();
	AnimationRowData m_currentAnimationData = AnimationRowData();

	// Physics
	PhysicsData m_physicsData = PhysicsData();
	
	// Collision
	bool m_bcollidingWithGround = false;

	// Components
	std::vector<Component*> m_components;
	InputComponent* m_inputComponent = nullptr;
	PhysicsComponent* m_physicsComponent = nullptr;
};

