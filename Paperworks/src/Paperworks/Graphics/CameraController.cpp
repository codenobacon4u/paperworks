#include "pwpch.h"
#include "CameraController.h"
#include <Paperworks\Core\Input.h>
#include <Paperworks\Core\KeyCodes.h>

namespace Paperworks {
	CameraController::CameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_Zoom, m_AspectRatio* m_Zoom, -m_Zoom, m_Zoom), m_Rotation(rotation)
	{
	}
	void CameraController::OnUpdate(Time t)
	{
		if (Input::IsKeyPressed(PW_KEY_W)) {
			m_CamPos.x += -sin(glm::radians(m_CamRot)) * m_CamTanslSpeed * t;
			m_CamPos.y += cos(glm::radians(m_CamRot)) * m_CamTanslSpeed * t;
		} else if (Input::IsKeyPressed(PW_KEY_S)) {
			m_CamPos.x -= -sin(glm::radians(m_CamRot)) * m_CamTanslSpeed * t;
			m_CamPos.y -= cos(glm::radians(m_CamRot)) * m_CamTanslSpeed * t;
		}
		
		if (Input::IsKeyPressed(PW_KEY_D)) {
			m_CamPos.x += cos(glm::radians(m_CamRot)) * m_CamTanslSpeed * t;
			m_CamPos.y += sin(glm::radians(m_CamRot)) * m_CamTanslSpeed * t;
		} else if (Input::IsKeyPressed(PW_KEY_A)) {
			m_CamPos.x -= cos(glm::radians(m_CamRot)) * m_CamTanslSpeed * t;
			m_CamPos.y -= sin(glm::radians(m_CamRot)) * m_CamTanslSpeed * t;
		}

		if (m_Rotation) {
			if (Input::IsKeyPressed(PW_KEY_E))
				m_CamRot += m_CamRotSpeed * t;
			else if (Input::IsKeyPressed(PW_KEY_Q))
				m_CamRot -= m_CamRotSpeed * t;

			m_Camera.SetRotation(m_CamRot);
		}

		m_Camera.SetPosition(m_CamPos);

		m_CamTanslSpeed = m_Zoom;
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(PW_BIND_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(PW_BIND_EVENT_FN(CameraController::OnWindowResized));
	}
	bool CameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_Zoom -= event.GetYOffset() * 0.25f;
		m_Zoom = std::max(m_Zoom, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
		return false;
	}
	bool CameraController::OnWindowResized(WindowResizeEvent& event)
	{
		m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
		return false;
	}
}