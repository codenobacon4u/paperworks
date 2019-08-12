#include "pwpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Paperworks {

	Camera::Camera(float left, float right, float bottom, float top)
		: m_Proj(glm::ortho(left, right, bottom, top, -1.f, 1.f)), m_View(1.f)
	{
	}

	void Camera::CalculateMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_Position) *
			glm::rotate(glm::mat4(1.f), glm::radians(m_Rotation), glm::vec3(0.f, 0.f, 1.f));

		m_View = glm::inverse(transform);
	}
}
