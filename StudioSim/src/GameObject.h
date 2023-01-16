#pragma once
#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

class Animate;

struct GameObjectData
{
	std::pair<float*,int> vertices;
	std::pair<float*,int> colors;
	std::pair<float*,int> textCoords;
};

class GameObject
{
public:
	GameObject(const GameObjectData& data, std::string texturePath);
	~GameObject();

	void Draw();

	inline VertexArray* GetVertexArray() { return m_va;  };
	inline Animate* GetAnimator() { return m_animator; }

private:

	Texture* m_texture;

	VertexArray* m_va;

	Animate* m_animator;
		
};

