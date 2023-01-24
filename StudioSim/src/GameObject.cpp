#include "GameObject.h"
#include "Animate.h"

GameObject::GameObject(std::string name, GameObjectData* data, const TransformData& transformData,
	const CollisionData& collisionData,
 const TextureData& textureData)
	: m_name(name), m_transform(new Transform(transformData.position, transformData.rotation, transformData.scale)),
	m_collisionData(collisionData), m_texture(new Texture(textureData)), m_data(data)
{
	m_va = new VertexArray();
	UpdateVertexArray();
}

GameObject::~GameObject()
{
	delete m_texture;
	m_texture = nullptr;

	delete m_va;
	m_va = nullptr;

	if (m_texture) delete m_texture;
	if (m_va) delete m_va;
	if (m_data) delete m_data;
}

void GameObject::Draw(Shader* mainShader)
{
	//Vector3 screenPosition = m_transform->GetPosition();
	//screenPosition.x /= 1280;
	//screenPosition.y /= 960;

	//glm::mat4 testMatrix = glm::mat4(1.0f);

	//Vector3 rotation = m_transform->GetRotation();

	//testMatrix = glm::scale(testMatrix, m_transform->GetScale());

	//// x
	//testMatrix = glm::rotate(testMatrix, glm::radians(rotation.x), Vector3(1.0f, 0.0f, 0.0f));
	//// y
	//testMatrix = glm::rotate(testMatrix, glm::radians(rotation.y), Vector3(0.0f, 1.0f, 0.0f));
	//// z
	//testMatrix = glm::rotate(testMatrix, glm::radians(rotation.z), Vector3(0.0f, 0.0f, 1.0f));

	//testMatrix = glm::translate(testMatrix, screenPosition);


	mainShader->SetMatrixUniform4("u_world", m_transform->GetTransformationMatrix());

	// draw square
	m_texture->Bind();
	m_va->Bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	
	m_texture->UnBind();
	m_va->Unbind();
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

void GameObject::UpdateObjectData(GameObjectData* newData)
{
	m_data = newData;
	UpdateVertexArray();
}

int const GameObject::GetGameObjectCollisionIndex(GameObject* gameObject)
{
	int i = 0;
	int indexToReturn = -1;

	for (GameObject* collidingGameObject : m_collidingObjects)
	{
		if (gameObject == collidingGameObject)
		{
			indexToReturn = i;
		}

		i++;
	}

	return indexToReturn;
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
		const int gameObjectIndex = GetGameObjectCollisionIndex(gameObject);
		m_collidingObjects.erase(m_collidingObjects.begin() + gameObjectIndex);
	}
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
