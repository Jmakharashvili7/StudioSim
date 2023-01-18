#include "GameObject.h"
#include "Animate.h"

GameObject::GameObject(GameObjectData* data, const TextureData& textureData) :
	m_texture(new Texture(textureData)), m_data(data)
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

void GameObject::Draw()
{
	// draw square
	m_texture->Bind();
	m_va->Bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	m_texture->UnBind();
	m_va->Unbind();
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
