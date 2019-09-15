#include "pwpch.h"
#include "Texture.h"

#include "Paperworks/Graphics/Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Paperworks {
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}
		return nullptr;
	}
}