#pragma once
#include <GL/glew.h>

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count; // number of indices

public:
	IndexBuffer();
	IndexBuffer(const unsigned int* size, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};