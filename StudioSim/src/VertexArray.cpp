#include "VertexArray.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_rendererID)); 
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		unsigned int offset = 0;

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}
 