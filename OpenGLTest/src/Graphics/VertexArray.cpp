#include "VertexArray.h"
#include <GLFW\glfw3.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_Renderer_ID); // generate 1 store id in vao var
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_Renderer_ID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(), (const void*)offset); // This binds the currently bound buffer to the VAO
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}

void VertexArray::Bind() const
{
	glBindVertexArray(m_Renderer_ID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);

}
