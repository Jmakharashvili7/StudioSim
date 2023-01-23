#include "GameObject.h"
#include "Animate.h"

GameObject::GameObject(GameObjectData* data, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData)
	: m_transform(new Transform(transformData.position, transformData.rotation, transformData.scale)),
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
	glm::vec3 screenPosition = m_transform->GetPosition();
	screenPosition.x /= 1280;
	screenPosition.y /= 960;

	glm::mat4 testMatrix = glm::mat4(1.0f);

	glm::vec3 rotation = m_transform->GetRotation();

	// x
	testMatrix = glm::rotate(testMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	// y
	testMatrix = glm::rotate(testMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	// z
	testMatrix = glm::rotate(testMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	testMatrix = glm::translate(testMatrix, screenPosition);

	testMatrix = glm::scale(testMatrix, m_transform->GetScale());


	mainShader->SetUniform4x4("u_model", m_transform->GetTransformationMatrix());

	// draw square
	m_texture->Bind();
	m_va->Bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	m_texture->UnBind();
	m_va->Unbind();
}

void GameObject::SetPosition(const glm::vec3 newPosition)
{
	m_transform->SetPosition(newPosition);
	SetCollisionCenter(glm::vec3(newPosition.x / 1280, newPosition.y / 960.0f, 0.0f));
}

void GameObject::AdjustPosition(const glm::vec3 adjustPosition)
{
	m_transform->AdjustPosition(adjustPosition);
	const glm::vec3 newPosition = m_transform->GetPosition();
	SetCollisionCenter(glm::vec3(newPosition.x / 1280, newPosition.y / 960.0f, 0.0f));
}

void GameObject::UpdateObjectData(GameObjectData* newData)
{
	m_data = newData;
	UpdateVertexArray();
}

void GameObject::AddCollision(GameObject* collidingObject, std::vector<CollisionSide>& sidesCollided)
{
	for (CollisionSide& collisionSide : sidesCollided)
	{
		if (collisionSide == CollisionSide::BOTTOM)
		{
			std::cout << "BOTTOM" << std::endl;
		}
		if (collisionSide == CollisionSide::LEFT)
		{
			std::cout << "LEFT" << std::endl;
		}
		if (collisionSide == CollisionSide::RIGHT)
		{
			std::cout << "RIGHT" << std::endl;
		}
		if (collisionSide == CollisionSide::TOP)
		{
			std::cout << "TOP" << std::endl;
		}

		//std::cout << sidesCollided.size() << std::endl;
	}
}

void GameObject::RemoveCollision(GameObject* gameObject)
{
	std::cout << "END COLLISION!" << std::endl;
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
