#include "Cube.h"

Cube::Cube()
{
	// init data

	float data[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 3 float for position, 2 float for texture "mapping"
	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // 3 float for position, 2 float for texture "mapping"
	 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	 0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.5f, 0.0f, 1.0f
	};

	// init indices

	unsigned int indices[] = {
		0,1,2,
		2,3,0,

		1,2,4,
		2,4,5,

		0,1,7,
		1,7,4,

		0,3,7,
		3,7,6,

		3,6,2,
		2,5,6,

		6,7,5,
		4,5,7
	};

	// init VA
	VertexArray va;
	VertexBuffer vb(data, 5 * 8 * sizeof(float)); // 5 floats per vertex * 8 vertex
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	// init ib
	// IndexBuffer ib(indices, 3 * 2 * 6); // 3 vertices * 2 triangles * 2 sides
}

Cube::~Cube()
{

}