#pragma once
#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

struct GameObjectData
{
	std::vector<float> vertices;
	std::vector<float> colors;
	std::vector<float> texCoords;
};

class GameObject
{
public:
	GameObject(GameObjectData* data, const std::string& texturePath);
	~GameObject();

	void Draw();
private:
	Texture* m_texture;
	VertexArray* m_va;
	GameObjectData* m_data;
};

