#include "pwpch.h"
#include "Shader.h"

#include "Paperworks/Graphics/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Paperworks {

	Shared<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateShared<OpenGLShader>(name, vertexSource, fragmentSource);
		}
		return nullptr;
	}
	
	Shared<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateShared<OpenGLShader>(path);
		}
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Shared<Shader>& shader)
	{
		PW_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Shared<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Shared<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Shared<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Shared<Shader> ShaderLibrary::Get(const std::string& name)
	{
		PW_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}