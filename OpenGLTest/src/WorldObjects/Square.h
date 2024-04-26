#pragma once
#include "WorldObject.h"
#include "../Graphics/Texture.h"

class Square : public WorldObject
{
public:
	Square();

	void BindTexture();
	void SetTransformation(glm::vec3 transform, glm::mat4 view, glm::mat4 proj);
	float m_Positions[16];
	unsigned int m_Indices[6];
};

