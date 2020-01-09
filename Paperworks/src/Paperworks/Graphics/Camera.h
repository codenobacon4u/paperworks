#pragma once

#include <glm/glm.hpp>

namespace Paperworks {
	class Camera
	{
	public:
		Camera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; CalculateMatrix(); }

		void SetProjection(float left, float right, float bottom, float top);

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; CalculateMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_Proj; }
		const glm::mat4& GetViewMatrix() const { return m_View; }
	private:
		void CalculateMatrix();
	private:
		glm::mat4 m_Proj;
		glm::mat4 m_View;

		glm::vec3 m_Position = glm::vec3(0.0f);
		float m_Rotation = 0.0f;
	};
}