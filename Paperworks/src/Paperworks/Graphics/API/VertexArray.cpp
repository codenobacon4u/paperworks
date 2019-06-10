#include "pwpch.h"

#include "Paperworks/Graphics/API/VertexArray.h"
#include "Paperworks/Graphics/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Paperworks {
	VertexArray* VertexArray::Create(BufferLayout layout)
	{
		switch (Renderer::GetAPI())
		{
		case API::None:
			return nullptr;
		case API::OpenGL:
			return new OpenGLVertexArray(layout);
		}
		return nullptr;
	}
}