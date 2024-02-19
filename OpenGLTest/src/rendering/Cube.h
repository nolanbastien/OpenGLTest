#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"


// #include "glm/glm.hpp" doesn't seem necessary
#include "glm/gtc/matrix_transform.hpp"

class Cube
{
public:
	Cube();
	~Cube();

	glm::vec3 position;
	glm::mat4 model;

	VertexArray va;
    IndexBuffer ib; // 3 vertices * 2 triangles * 2 sides

	void UpdateModel();
};