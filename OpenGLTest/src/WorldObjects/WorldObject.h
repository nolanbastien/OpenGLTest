#pragma once

#include "../Graphics/Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class WorldObject
{

public:
	WorldObject();
	Renderer m_Renderer;

	VertexArray m_Va;
	IndexBuffer m_Ib;
	Shader m_Shader;
	
	VertexBuffer m_Vb;
	VertexBufferLayout m_VbLayout;

	void ClearAll() const;
	void Render() const; 
};

