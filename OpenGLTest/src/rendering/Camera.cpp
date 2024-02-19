#include "Camera.h"

Camera::Camera()
{
	pos = glm::vec3(0.0f, 0.0f, 5.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::normalize(glm::cross(front, up));

	UpdateView();
}


Camera::~Camera()
{

}

void Camera::UpdateView()
{
	view = glm::lookAt(pos, pos + front, up);
}

void Camera::UpdateFromInput()
{
}

