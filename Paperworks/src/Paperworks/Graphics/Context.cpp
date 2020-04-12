#include "pwpch.h"
#include "Context.h"

#include "Paperworks/Graphics/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Paperworks {
	Unique<Context> Context::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateUnique<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}
		return nullptr;
	}
}
