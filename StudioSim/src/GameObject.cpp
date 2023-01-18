#include "GameObject.h"
#include "Animate.h"

GameObject::GameObject(GameObjectData* data, const std::string& texturePath) :
	m_texture(new Texture(texturePath)), m_data(data)
{
	m_Transform = new Transform();
	m_va = new VertexArray();
	UpdateVertexArray();
}

GameObject::~GameObject()
{
	delete m_texture;
	m_texture = nullptr;

	delete m_va;
	m_va = nullptr;

	delete m_animator;
	m_animator = nullptr;
	if (m_texture) delete m_texture;
	if (m_va) delete m_va;
	if (m_data) delete m_data;
}

void GameObject::Draw(Shader* shaderToUse)
{
	if (shaderToUse)
	{
		
	

		vec2 testPosition(500, 500);
		testPosition.x = testPosition.x / 1280;
		testPosition.y = testPosition.y / 960;
		glm::mat4 testMatrix = glm::mat4(1.0f);
		testMatrix = glm::translate(testMatrix, vec3(testPosition, 0.0f));

		shaderToUse->SetUniform4x4("u_model", m_Transform->GetWorldTransform());
		// draw square
		m_texture->Bind();
		m_va->Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
		m_texture->UnBind();
		m_va->Unbind();
	}
}

void GameObject::SetUpAnimator(int rows, int columns)
{
	m_animator = new Animate(this, rows, columns);
}

void GameObject::UpdateObjectData(GameObjectData* newData)
{
	m_data = newData;
	UpdateVertexArray();
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
