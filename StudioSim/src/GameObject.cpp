#include "GameObject.h"

GameObject::GameObject(const GameObjectData& data, std::string texturePath) :
	m_texture(new Texture(texturePath))
{
	m_va = new VertexArray();
	VertexBuffer vertexBuffer = VertexBuffer(data.vertices.first, data.vertices.second);
	VertexBuffer colorBuffer = VertexBuffer(data.colors.first, data.colors.second);
	VertexBuffer texCoordsBuffer = VertexBuffer(data.textCoords.first, data.textCoords.second);

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

void GameObject::Draw()
{
	// draw square
	m_texture->Bind();
	m_va->Bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	m_texture->UnBind();
	m_va->Unbind();
}
