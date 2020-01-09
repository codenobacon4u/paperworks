#include "pwpch.h"
#include "Texture.h"

#include "Paperworks/Graphics/Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Paperworks {
	Shared<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateShared<OpenGLTexture2D>(width, height);
		}
		return nullptr;
	}

	Shared<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateShared<OpenGLTexture2D>(path);
		}
		return nullptr;
	}
}