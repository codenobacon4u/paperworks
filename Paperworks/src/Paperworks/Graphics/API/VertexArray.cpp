#include "pwpch.h"

#include "Paperworks/Graphics/API/VertexArray.h"
#include "Paperworks/Graphics/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Paperworks {
	Shared<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateShared<OpenGLVertexArray>();
		}
		return nullptr;
	}
}