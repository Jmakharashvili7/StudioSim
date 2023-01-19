#pragma once
#include "BasicIncludes.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

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
	GameObject(std::string name, GameObjectData* data, const std::string& texturePath);
	~GameObject();

	void Draw();
	void SetUpAnimator(int rows, int columns);

	inline VertexArray* GetVertexArray() { return m_va;  };
	inline Animate* GetAnimator() { return m_animator; }
	inline GameObjectData* GetGameObjectData() { return m_data; }
	inline Texture* GetTexture() const { return m_texture; }
	inline std::string GetName() const { return m_name; }

	void UpdateVertexArray();
	void UpdateObjectData(GameObjectData* newData);

private:
	std::string m_name;
	Texture* m_texture;
	VertexArray* m_va;
	Animate* m_animator;
	GameObjectData* m_data;
};

