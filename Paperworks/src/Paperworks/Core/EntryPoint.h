#pragma once

#include "Paperworks/Core/Core.h"

#if defined(PW_PLATFORM_WINDOWS) || defined(PW_PLATFORM_LINUX)
extern Paperworks::Application* Paperworks::CreateApplication();

int main(int argc, char** argv)
{
	Paperworks::Log::Init();

	auto app = Paperworks::CreateApplication();
	app->Run();
	delete app;
}
#endif // PW_PLATFORM_WINDOWS