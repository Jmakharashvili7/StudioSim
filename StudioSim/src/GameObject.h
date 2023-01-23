#pragma once
#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "QuackDataTypes.h"
#include "Shader.h"
#include "Transform.h"

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

	// Position
	virtual void SetPosition(const glm::vec3 newPosition) { if (m_transform) m_transform->SetPosition(newPosition); }
	virtual void AdjustPosition(const glm::vec3 adjustPosition) { if (m_transform) m_transform->AdjustPosition(adjustPosition); }
	inline const glm::vec3 GetPosition() const { if (m_transform) return m_transform->GetPosition(); }

	// Rotation
	virtual glm::vec3 GetRotation() const { if (m_transform) return m_transform->GetRotation(); }
	virtual void SetRotation(const glm::vec3 newRotation) { if (m_transform) m_transform->SetRotation(newRotation); }
	virtual void AdjustRotation(const glm::vec3 adjustRotation) { if (m_transform) m_transform->AdjustRotation(adjustRotation); }
	virtual void SetRotationAroundPivot(const glm::vec3 pivotPosition, const glm::vec3 newRotation) { if (m_transform) m_transform->SetRotationAroundPivot(pivotPosition, newRotation); }

	// Scale
	virtual glm::vec3 GetScale() const { if (m_transform) return m_transform->GetScale(); }
	virtual void SetScale(const glm::vec3 newScale) { if (m_transform) m_transform->SetScale(newScale); }
	virtual void AdjustScale(const glm::vec3 adjustScale) { if (m_transform) m_transform->AdjustScale(adjustScale); }

	inline VertexArray* GetVertexArray() { return m_va;  };
	inline GameObjectData* GetGameObjectData() { return m_data; }
	inline Texture* GetTexture() const { return m_texture; }
	inline std::string GetName() const { return m_name; }

	void UpdateVertexArray();
	void UpdateObjectData(GameObjectData* newData);

protected:
	std::string m_name;
	Texture* m_texture;
	VertexArray* m_va;
		
	GameObjectData* m_data;

	Transform* m_transform;
};

