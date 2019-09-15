#pragma once

#include "Paperworks/Graphics/Shader.h"

typedef unsigned int GLenum;

namespace Paperworks {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader();

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vec);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vec);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vec);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		void Bind() const;
		void Unbind() const;
	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
		void Compile(const std::unordered_map<GLenum, std::string>& shaders);
	private:
		uint32_t m_RendererID;
	};
}