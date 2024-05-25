#pragma once

#include "../rendering/VertexArray.h"
#include "../rendering/IndexBuffer.h"
#include "../rendering/TextureCube.h"


// #include "glm/glm.hpp" doesn't seem necessary
#include "glm/gtc/matrix_transform.hpp"

class Cube
{
public:
	Cube();
	~Cube();

	glm::vec3 m_Position;
	glm::mat4 model;

	VertexArray va;
    IndexBuffer ib; // 3 vertices * 2 triangles * 2 sides

	TextureCube m_TextureCube;

	void UpdateModel();
};