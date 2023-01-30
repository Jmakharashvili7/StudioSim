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
#include "QuackOperations.h"

enum class GameObjectType
{
	OBJECT,
	ACTOR,
	CHARACTER
};

struct VertexData
{
	std::vector<float> vertices;
	std::vector<float> colors;
	std::vector<float> texCoords;
};

class GameObject
{
public:
	GameObject(std::string name, VertexData* data, const TransformData& transformData, const CollisionData& collisionData, const std::string& textureName);
	virtual ~GameObject();

	// Rendering
	virtual void Draw(Shader* mainShader);

	// Update
	virtual void Update(const float deltaTime);

	// Position
	virtual void SetPosition(const Vector3 newPosition);
	virtual void AdjustPosition(const Vector3 adjustPosition);
	inline const Vector3 GetPosition() const { if (m_transform) return m_transform->GetPosition(); }
	inline const Vector3 GetPreviousPosition() const { if (m_transform) return m_transform->GetPreviousPosition(); }
	inline TransformData GetTransformData() { return m_transformData; }
	inline Transform* GetTransform() { return m_transform; }

	// Rotation
	virtual Vector3 GetRotation() const { if (m_transform) return m_transform->GetRotation(); }
	virtual void SetRotation(const Vector3 newRotation) { if (m_transform) m_transform->SetRotation(newRotation); }
	virtual void AdjustRotation(const Vector3 adjustRotation) { if (m_transform) m_transform->AdjustRotation(adjustRotation); }
	virtual void SetRotationAroundPivot(const Vector3 pivotPosition, const float newRotation) { if (m_transform) m_transform->SetRotationAroundPivot(pivotPosition, newRotation); }

	// Scale
	virtual Vector3 GetScale() const { if (m_transform) return m_transform->GetScale(); }
	virtual void SetScale(const Vector3 newScale);
	virtual void AdjustScale(const Vector3 adjustScale);

	// Collision
	inline void SetCollisionData(const CollisionData& newCollisionData) { m_collisionData = newCollisionData; }
	inline void SetCollisionType(const CollisionType newCollisionType) { m_collisionData.collisionType = newCollisionType; }
	inline void SetCollisionCenter(const Vector3 newCenterPosition) { m_collisionData.centerPosition = newCenterPosition; }
	inline void SetCollisionBoxSize(const Vector3 newSize) { m_collisionData.size = newSize; }
	inline void SetCollisionSphereRadius(const float newRadius) { m_collisionData.radius = newRadius; }
	inline const CollisionData& const GetCollisionData() { return m_collisionData; }
	inline const CollisionType const GetCollisionType() { return m_collisionData.collisionType; }
	inline const Vector3 const GetCollisionCenter() { return m_collisionData.centerPosition; }
	inline const Vector3 const GetCollisionBoxSize() { return m_collisionData.size; }
	inline const float const GetCollisionSphereRadius() { return m_collisionData.radius; }
	const bool const GetIsCollidingGameObject(GameObject* gameObject);
	virtual void AddCollision(GameObject* collidingObject);
	virtual void RemoveCollision(GameObject* gameObject);

	// Other
	inline const std::string const GetName() { return m_name; }

	// Object
	inline VertexArray* GetVertexArray() { return m_va;  };
	inline VertexData* GetGameObjectData() { return m_data; }
	inline Texture* GetTexture() const { return m_texture; }
	inline std::string GetTextureName() { return m_textureName; }
	inline void SetTextureName(std::string textureName) { m_textureName = textureName; }

	// Name + type
	inline std::string GetName() const { return m_name; }
	inline GameObjectType GetType() const { return m_type; }

	void UpdateVertexArray();
	void UpdateObjectData(VertexData* newData);

	void SetNewTexture(std::string newPath);
protected:
	// Name + type
	std::string m_name = "";
	GameObjectType m_type;

	// Texture
	Texture* m_texture = nullptr;
	std::string m_textureName;

	// Object
	VertexArray* m_va = nullptr;
	VertexData* m_data = nullptr;
	Transform* m_transform = nullptr;
	TransformData m_transformData;

	// Collision
	CollisionData m_collisionData = CollisionData();
	std::vector<GameObject*> m_collidingObjects;
};

