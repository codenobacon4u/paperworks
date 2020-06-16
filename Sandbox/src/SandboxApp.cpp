#include <Paperworks.h>
#include <Paperworks/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "DebugLayer.h"

class Sandbox : public Paperworks::Application
{
public:
	Sandbox() 
	{
		//PushLayer(new DebugLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {

	}
};

Paperworks::Application* Paperworks::CreateApplication() {
	return new Sandbox();
}