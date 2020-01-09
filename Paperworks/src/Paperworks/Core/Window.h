#pragma once

#include "pwpch.h"

#include "Paperworks/Core/Core.h"
#include "Paperworks/Events/Event.h"

namespace Paperworks {
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Paperworks Engine",
					unsigned int width = 1920, unsigned int height = 1080)
			: Title(title), Width(width), Height(height) {}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		// Gets the actual window object for the platform
		virtual void* GetNativeWindow() const = 0;

		static Unique<Window> Create(const WindowProps& props = WindowProps());
	};
}