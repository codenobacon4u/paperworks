#include <Paperworks.h>

class ExampleLayer : public Paperworks::Layer
{
public:
	ExampleLayer()
		: Layer("Example") 
	{
	}

	void OnUpdate() override
	{
		//PW_INFO("ExampleLayer::Update");
		if (Paperworks::Input::IsKeyPressed(PW_KEY_TAB))
			PW_INFO("Tab key pressed");
	}

	void OnEvent(Paperworks::Event& event) override
	{
		//PW_TRACE("{0}", event);
	}
};

class Sandbox : public Paperworks::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Paperworks::Application* Paperworks::CreateApplication() {
	return new Sandbox();
}