#include <Paperworks.h>

class DebugLayer : public Paperworks::Layer
{
public:
	DebugLayer()
		: Layer("Debug") 
	{
	}

	void OnUpdate() override
	{
		
	}

	void OnEvent(Paperworks::Event& event) override
	{
		if (event.GetEventType() == Paperworks::EventType::WindowResize) {
			PW_CORE_TRACE("{0}", event.ToString());
		}
	}
};

class Sandbox : public Paperworks::Application
{
public:
	Sandbox() {
		PushLayer(new DebugLayer());
	}

	~Sandbox() {

	}
};

Paperworks::Application* Paperworks::CreateApplication() {
	return new Sandbox();
}