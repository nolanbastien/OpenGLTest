#pragma once

#include "../rendering/Camera.h"
#include "../rendering/Cube.h"
#include "../rendering/TextureCube.h"

class World
{
public:
	std::vector<Cube*> m_cubeObjects;

	World();
	int PlayerTouchedCube(float x, float y, float z);
	void Draw(Camera& cam, Shader& shader, Renderer& renderer, TextureCube& texture, glm::mat4& proj);
};

