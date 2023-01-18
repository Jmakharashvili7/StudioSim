#pragma once
#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "QuackDataTypes.h"

struct GameObjectData
{
	std::vector<float> vertices;
	std::vector<float> colors;
	std::vector<float> texCoords;
};

class GameObject
{
public:
	GameObject(GameObjectData* data, const TextureData& textureData);
	~GameObject();

	virtual void Draw();

	inline VertexArray* GetVertexArray() { return m_va;  };
	inline GameObjectData* GetGameObjectData() { return m_data; }

	void UpdateVertexArray();
	void UpdateObjectData(GameObjectData* newData);

protected:
	Texture* m_texture;

	VertexArray* m_va;
		
	GameObjectData* m_data;
};

