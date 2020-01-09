#pragma once

#include "Paperworks/Graphics/Camera.h"
#include "Paperworks/Core/Time.h"

#include "Paperworks/Events/ApplicationEvent.h"
#include "Paperworks/Events/MouseEvent.h"

namespace Paperworks {
	class CameraController
	{
	public:
		CameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Time t);
		void OnEvent(Event& e);

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

		glm::vec3 GetPosition() const { return m_CamPos; }

		float GetZoom() const { return m_Zoom; }
		void SetZoom(float level) { m_Zoom = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizeEvent& event);
	private:
		float m_AspectRatio;
		float m_Zoom = 1.0f;
		Camera m_Camera;
		
		bool m_Rotation;

		glm::vec3 m_CamPos = { 0.0f, 0.0f, 0.0f };
		float m_CamRot = 0.0f;
		float m_CamTanslSpeed = 5.0f, m_CamRotSpeed = 180.0f;
	};
}