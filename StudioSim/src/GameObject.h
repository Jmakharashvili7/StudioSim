#pragma once
#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "QuackDataTypes.h"

class Animate;

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

	void Draw();
	void SetUpAnimator(int rows, int columns);

	inline VertexArray* GetVertexArray() { return m_va;  };
	inline Animate* GetAnimator() { return m_animator; }
	inline GameObjectData* GetGameObjectData() { return m_data; }

	void UpdateVertexArray();
	void UpdateObjectData(GameObjectData* newData);

protected:
	Texture* m_texture;

	VertexArray* m_va;

	Animate* m_animator;
		
	GameObjectData* m_data;
};

