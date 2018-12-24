#pragma once

#ifdef PW_PLATFORM_WINDOWS
extern Paperworks::Application* Paperworks::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Paperworks::CreateApplication();
	app->Run();
	delete app;
}
#endif // PW_PLATFORM_WINDOWS
