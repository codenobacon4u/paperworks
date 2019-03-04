#pragma once

#include "Paperworks/Layer.h"
#include "Paperworks/Events/KeyEvent.h"
#include "Paperworks/Events/MouseEvent.h"
#include "Paperworks/Events/ApplicationEvent.h"

namespace Paperworks {
	class PAPERWORKS_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}