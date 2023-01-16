#pragma once
#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

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

private:
	Texture* m_texture;
	VertexArray* m_va;
};

