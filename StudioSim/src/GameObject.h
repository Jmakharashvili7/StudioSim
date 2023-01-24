#pragma once
#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "QuackDataTypes.h"
#include "Shader.h"
#include "Transform.h"
#include "component.h"
#include "InputComponent.h"

struct GameObjectData
{
	std::vector<float> vertices;
	std::vector<float> colors;
	std::vector<float> texCoords;
};

class GameObject
{
public:
	GameObject(std::string name, GameObjectData* data, const TransformData& transformData, const TextureData& textureData);
	~GameObject();

	virtual void Draw(Shader* mainShader);
	virtual void Update(float deltaTime);

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

	inline VertexArray* GetVertexArray() { return m_va;  };
	inline GameObjectData* GetGameObjectData() { return m_data; }
	inline Texture* GetTexture() const { return m_texture; }
	inline std::string GetName() const { return m_name; }

	void UpdateVertexArray();
	void UpdateObjectData(GameObjectData* newData);

	void AddComponent(Component* comp);
	void RemoveComponent(Component* comp);

	Component* GetComponent(int Order) {
		for (Component* comp : m_Components)
		{
			if (comp->GetComponentFromUpdateOrder(Order) != nullptr)
			{
				return comp->GetComponentFromUpdateOrder(Order);
			}
		}
		return nullptr;
	}

protected:
	std::string m_name;
	Texture* m_texture;
	VertexArray* m_va;
		Transform* m_transform;
	GameObjectData* m_data;
	vector<Component*> m_Components;

	

	
};

