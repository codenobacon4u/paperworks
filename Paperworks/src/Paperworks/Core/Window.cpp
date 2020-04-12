#include "pwpch.h"
#include "Window.h"

#ifdef PW_PLATFORM_WINDOWS
#include "Platform/Windows/WinWindow.h"
#endif

namespace Paperworks {
	Unique<Window> Window::Create(const WindowProps& props)
	{
#ifdef PW_PLATFORM_WINDOWS
		return CreateUnique<WinWindow>(props);
#else
		return nullptr;
#endif
	}
}