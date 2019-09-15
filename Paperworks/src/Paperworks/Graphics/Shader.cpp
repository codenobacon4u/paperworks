#include "pwpch.h"
#include "Shader.h"

#include "Paperworks/Graphics/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Paperworks {

	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSource, fragmentSource);
		}
		return nullptr;
	}
	Shader* Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(path);
		}
		return nullptr;
	}
}