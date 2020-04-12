#pragma once

#include "Paperworks/Core/Window.h"

#include <GLFW/glfw3.h>

#include "Paperworks/Graphics/Context.h"

namespace Paperworks {
	class WinWindow : public Window
	{
	public:
		/**
			Initializes a new WinWindow object for use on Windows.

			@param props The properties of the window.
		*/
		WinWindow(const WindowProps& props);
		virtual ~WinWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		
		virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		Unique<Context> m_Context;
		
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}