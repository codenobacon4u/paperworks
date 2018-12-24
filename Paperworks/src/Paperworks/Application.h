#pragma once

#include "Core.h"

namespace Paperworks {
	class PAPERWORKS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}
