#pragma once

#include "Window.h"

#include "Paperworks/Core/Core.h"
#include "Paperworks/Core/LayerStack.h"
#include "Paperworks/Core/Time.h"

#include "Paperworks/Events/Event.h"
#include "Paperworks/Events/ApplicationEvent.h"

#include "Paperworks/ImGui/ImGuiLayer.h"

#include "Paperworks/Graphics/Shader.h"
#include "Paperworks/Graphics/API/Buffer.h"
#include "Paperworks/Graphics/API/VertexArray.h"
#include "Paperworks/Graphics/Camera.h"

int main(int argc, char** argv);

namespace Paperworks {
	class Application
	{
	public:
		Application(const std::string& name = "Paperworks Engine");
		virtual ~Application();

		void Close();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }
	private:
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Unique<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true, m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrame = 0.0f;

		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}
