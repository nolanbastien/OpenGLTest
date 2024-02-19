#pragma once

#include "Renderer.h"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
public:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 direction;
	glm::vec3 absolute_up;
	glm::vec3 right;
	glm::vec3 up;
	glm::mat4 view;

	Camera();
	~Camera();

	void UpdateView();
	void UpdateFromInput();

};

