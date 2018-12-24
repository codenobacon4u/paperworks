#include <Paperworks.h>

class Sandbox : public Paperworks::Application
{
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Paperworks::Application* Paperworks::CreateApplication() {
	return new Sandbox();
}