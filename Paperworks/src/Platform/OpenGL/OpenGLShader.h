#pragma once

#include "Paperworks/Graphics/Shader.h"

typedef unsigned int GLenum;

namespace Paperworks {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader();

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& vec) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& vec) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& vec) override;
		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* value, uint32_t count);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		void UploadUniformMat3(const std::string& name, const glm::mat3& value);
		void UploadUniformMat4(const std::string& name, const glm::mat4& value);

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
		void Compile(const std::unordered_map<GLenum, std::string>& shaders);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}