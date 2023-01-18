#pragma once
#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Shader.h"

#include "IdkYet/Transform.h"

using namespace glm;

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
	GameObject(GameObjectData* data, const std::string& texturePath);
	~GameObject();

	void Draw(Shader* shaderToUse);
	void SetUpAnimator(int rows, int columns);

	inline VertexArray* GetVertexArray() { return m_va;  };
	inline Animate* GetAnimator() { return m_animator; }
	inline GameObjectData* GetGameObjectData() { return m_data; }

	void UpdateVertexArray();
	void UpdateObjectData(GameObjectData* newData);

private:
	Texture* m_texture;

	VertexArray* m_va;

	Animate* m_animator;
		
	GameObjectData* m_data;
	Transform* m_Transform;
};

