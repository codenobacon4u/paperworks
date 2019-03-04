#pragma once

#include "Window.h"
#include "Paperworks/Core.h"
#include "Paperworks/LayerStack.h"
#include "Paperworks/Events/Event.h"
#include "Paperworks/ImGui/ImGuiLayer.h"
#include "Paperworks/Events/ApplicationEvent.h"

namespace Paperworks {
	class PAPERWORKS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
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
		static Application* s_Instance;
	};

	Application* CreateApplication();
}
