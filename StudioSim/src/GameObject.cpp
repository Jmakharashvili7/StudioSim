#include "GameObject.h"
#include "Animate.h"
#include "Quack.h"

GameObject::GameObject(std::string name, GameObjectData* data, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData)
	: m_name(name), m_transform(new Transform(transformData.position, transformData.rotation, transformData.scale)),
	m_collisionData(collisionData), m_texture(new Texture(textureData)), m_data(data), m_textureData(textureData), m_transformData(transformData) 
{
	m_type = GameObjectType::OBJECT;
	m_va = new VertexArray();
	UpdateVertexArray();
	
	std::cout << "FELYPE LIKES GOTHS" << std::endl;
}

GameObject::~GameObject()
{
	delete m_texture;
	m_texture = nullptr;

	delete m_va;
	m_va = nullptr;

	delete m_data;
	m_data = nullptr;

	delete m_transform;
	m_transform = nullptr;
}

void GameObject::Draw(Shader* mainShader)
{
	Vector3 screenPosition = m_transform->GetPosition();

	mainShader->SetMatrixUniform4("u_world", m_transform->GetTransformationMatrix());

	// draw square
	m_texture->Bind();
	m_va->Bind();

	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	
	m_texture->UnBind();
	m_va->Unbind();
}

void GameObject::Update(const float deltaTime)
{

}

void GameObject::SetPosition(const Vector3 newPosition)
{
	m_transform->SetPosition(newPosition);
	SetCollisionCenter(newPosition);
}

void GameObject::AdjustPosition(const Vector3 adjustPosition)
{
	m_transform->AdjustPosition(adjustPosition);
	const Vector3 newPosition = m_transform->GetPosition();
	SetCollisionCenter(newPosition);
}

void GameObject::SetScale(const Vector3 newScale)
{
	m_transform->SetScale(newScale);
	SetCollisionBoxSize(newScale);
}

void GameObject::AdjustScale(const Vector3 adjustScale)
{
	m_transform->AdjustScale(adjustScale);
	const Vector3 newScale = m_transform->GetScale();
	SetCollisionBoxSize(newScale);
}

void GameObject::UpdateObjectData(GameObjectData* newData)
{
	m_data = newData;
	UpdateVertexArray();
}

bool const GameObject::GetIsCollidingGameObject(GameObject* gameObject)
{
	bool bFound = false;

	for (GameObject* collidingGameObject : m_collidingObjects)
	{
		if (gameObject == collidingGameObject)
		{
			bFound = true;
			break;
		}
	}

	return bFound;
}

void GameObject::AddCollision(GameObject* collidingObject)
{
	//std::cout << "START COLLISION!" << std::endl;
	if (collidingObject)
	{
		m_collidingObjects.push_back(collidingObject);
	}
}

void GameObject::RemoveCollision(GameObject* gameObject)
{
	//std::cout << "END COLLISION!" << std::endl;
	if (gameObject)
	{
		const int gameObjectIndex = QuackOperations::GetGameObjectIndex(gameObject, m_collidingObjects);
		m_collidingObjects.erase(m_collidingObjects.begin() + gameObjectIndex);
	}
}

void GameObject::Destroy()
{
	//Quack::DestroyGameObject(this);
}

void GameObject::UpdateVertexArray()
{
	VertexBuffer vertexBuffer = VertexBuffer(m_data->vertices.data(), m_data->vertices.size() * sizeof(float));
	VertexBuffer colorBuffer = VertexBuffer(m_data->colors.data(), m_data->colors.size() * sizeof(float));
	VertexBuffer texCoordsBuffer = VertexBuffer(m_data->texCoords.data(), m_data->texCoords.size() * sizeof(float));

	VertexBufferLayout vertexLayout;
	vertexLayout.Push<float>(3);

	VertexBufferLayout colorLayout;
	colorLayout.Push<float>(3);

	VertexBufferLayout texCoordsLayout;
	texCoordsLayout.Push<float>(2);

	m_va->AddBuffer(vertexBuffer, vertexLayout, VertexType::VERTEX);
	m_va->AddBuffer(colorBuffer, colorLayout, VertexType::COLOR);
	m_va->AddBuffer(texCoordsBuffer, texCoordsLayout, VertexType::TEX_COORDS);
}
