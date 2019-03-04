#pragma once

#ifdef PW_PLATFORM_WINDOWS
extern Paperworks::Application* Paperworks::CreateApplication();

int main(int argc, char** argv)
{
	Paperworks::Log::Init();
	PW_CORE_WARN("Initialized Log!");
	PW_INFO("Initialized Log!");

	auto app = Paperworks::CreateApplication();
	app->Run();
	delete app;
}
#endif // PW_PLATFORM_WINDOWS