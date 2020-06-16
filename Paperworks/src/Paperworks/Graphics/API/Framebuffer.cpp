#include "pwpch.h"

#include "Framebuffer.h"
#include "Paperworks/Graphics/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Paperworks {

	Shared<Framebuffer> Framebuffer::Create(const FramebufferSpec& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateShared<OpenGLFramebuffer>(spec);
		}
		return nullptr;
	}
}