#include "pwpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Paperworks {
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Unique<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPI::API::None: PW_CORE_ASSERT(false, "RendererAPI::None Not supported!")
			case RendererAPI::API::OpenGL: return Unique<OpenGLRendererAPI>();
		}
		PW_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}
}