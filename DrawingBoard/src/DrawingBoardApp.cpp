#include <Paperworks.h>
#include <Paperworks/Core/EntryPoint.h>

#include "EditorLayer.h"

class DrawingBoard : public Paperworks::Application
{
public:
	DrawingBoard() 
		: Application ("DrawingBoard")
	{
		PushLayer(new EditorLayer());
	}

	~DrawingBoard() {

	}
};

Paperworks::Application* Paperworks::CreateApplication() {
	return new DrawingBoard();
}