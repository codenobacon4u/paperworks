#pragma once

#include "Window.h"
#include "Paperworks/Core.h"
#include "Paperworks/LayerStack.h"
#include "Paperworks/Events/Event.h"
#include "Paperworks/Graphics/Shader.h"
#include "Paperworks/ImGui/ImGuiLayer.h"
#include "Paperworks/Events/ApplicationEvent.h"

namespace Paperworks {
	class Application
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

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}
