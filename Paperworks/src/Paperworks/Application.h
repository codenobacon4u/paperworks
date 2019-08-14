#pragma once

#include "Window.h"
#include "Paperworks/Core.h"
#include "Paperworks/LayerStack.h"
#include "Paperworks/Events/Event.h"
#include "Paperworks/Graphics/Shader.h"
#include "Paperworks/ImGui/ImGuiLayer.h"
#include "Paperworks/Events/ApplicationEvent.h"
#include "Paperworks/Graphics/API/Buffer.h"
#include "Paperworks/Graphics/API/VertexArray.h"
#include "Paperworks/Graphics/Camera.h"
#include "Paperworks/Core/Time.h"

namespace Paperworks {
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Close();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrame = 0.0f;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}
