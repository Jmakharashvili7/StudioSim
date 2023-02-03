#include "pch.h"

#include "Renderer.h"

std::vector<VertexArray*> Renderer::m_objects;

void Renderer::DrawLine(glm::vec3 p0, glm::vec3 p1, glm::vec3 color)
{
	float vertices[] = { p0.x, p0.y, p0.z, 
						 p1.x, p1.y, p1.z };

	VertexBuffer vb = { vertices, sizeof(float) * 6 };
	VertexBufferLayout vblVer;
	vblVer.Push<float>(3);

	float colors[] = { color.x, color.y, color.z,
					   color.x, color.y, color.z };
	
	VertexBuffer vbc = { colors, sizeof(float) * 6};
	VertexBufferLayout vblCol;
	vblCol.Push<float>(3);

	VertexArray* va = new VertexArray();
	va->AddBuffer(vb, vblVer, VertexType::VERTEX);
	va->AddBuffer(vbc, vblCol, VertexType::COLOR);

	m_objects.push_back(va);
}

void Renderer::DrawDebugLines()
{
	for (VertexArray* line : m_objects)
	{
		line->Bind();
		glDrawArrays(GL_LINES, 0, 2);
		line->Unbind();
	}
}
