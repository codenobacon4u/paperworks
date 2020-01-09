#pragma once

#include "Paperworks/Graphics/Shader.h"

typedef unsigned int GLenum;

namespace Paperworks {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader();

		virtual void SetInt(const std::string& name, int value) override;

		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& vec) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& vec) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& vec) override;
		
		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;

		void Bind() const;
		void Unbind() const;
	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
		void Compile(const std::unordered_map<GLenum, std::string>& shaders);
	private:
		uint32_t m_RendererID;
	};
}