#pragma once
#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "QuackDataTypes.h"
#include "Shader.h"
#include "Transform.h"
#include "QuackPhysics.h"

struct GameObjectData
{
	std::vector<float> vertices;
	std::vector<float> colors;
	std::vector<float> texCoords;
};

class GameObject
{
public:
	GameObject(std::string name, GameObjectData* data, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData);
	~GameObject();

	virtual void Draw(Shader* mainShader);

	// Position
	virtual void SetPosition(const Vector3 newPosition) { if (m_transform) m_transform->SetPosition(newPosition); }
	virtual void AdjustPosition(const Vector3 adjustPosition) { if (m_transform) m_transform->AdjustPosition(adjustPosition); }
	inline const Vector3 GetPosition() const { if (m_transform) return m_transform->GetPosition(); }

	// Rotation
	virtual void SetRotation(const Vector3 newRotation) { if (m_transform) m_transform->SetRotation(newRotation); }
	virtual void AdjustRotation(const Vector3 adjustRotation) { if (m_transform) m_transform->AdjustRotation(adjustRotation); }
	virtual void SetRotationAroundPivot(const Vector3 pivotPosition, const float newRotation) { if (m_transform) m_transform->SetRotationAroundPivot(pivotPosition, newRotation); }

	// Scale
	virtual void SetScale(const Vector3 newScale) { if (m_transform) m_transform->SetScale(newScale); }
	virtual void AdjustScale(const Vector3 adjustScale) { if (m_transform) m_transform->AdjustScale(adjustScale); }

	// Collision
	inline void SetCollisionData(const CollisionData& newCollisionData) { m_collisionData = newCollisionData; }
	inline void SetCollisionType(const CollisionType newCollisionType) { m_collisionData.collisionType = newCollisionType; }
	inline void SetCollisionCenter(const glm::vec3 newCenterPosition) { m_collisionData.centerPosition = newCenterPosition; }
	inline void SetCollisionBoxSize(const glm::vec3 newSize) { m_collisionData.size = newSize; }
	inline void SetCollisionSphereRadius(const float newRadius) { m_collisionData.radius = newRadius; }
	inline const CollisionData& const GetCollisionData() { return m_collisionData; }
	inline const CollisionType const GetCollisionType() { return m_collisionData.collisionType; }
	inline const glm::vec3 const GetCollisionCenter() { return m_collisionData.centerPosition; }
	inline const glm::vec3 const GetCollisionBoxSize() { return m_collisionData.size; }
	inline const float const GetCollisionSphereRadius() { return m_collisionData.radius; }
	const int const GetGameObjectCollisionIndex(GameObject* gameObject);
	const bool const GetIsCollidingGameObject(GameObject* gameObject);
	virtual void AddCollision(GameObject* collidingObject);
	virtual void RemoveCollision(GameObject* gameObject);

	// Other
	inline const std::string const GetName() { return m_name; }

	inline VertexArray* GetVertexArray() { return m_va;  };
	inline GameObjectData* GetGameObjectData() { return m_data; }
	inline Texture* GetTexture() const { return m_texture; }
	inline std::string GetName() const { return m_name; }

	void UpdateVertexArray();
	void UpdateObjectData(GameObjectData* newData);
	

protected:
	std::string m_name = "";

	Texture* m_texture = nullptr;
	VertexArray* m_va = nullptr;
	GameObjectData* m_data = nullptr;
	Transform* m_transform = nullptr;

	/* Collision */
	CollisionData m_collisionData = CollisionData();
	std::vector<GameObject*> m_collidingObjects;
};

