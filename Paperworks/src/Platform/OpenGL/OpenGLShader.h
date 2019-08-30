#pragma once

#include "Paperworks/Graphics/Shader.h"

namespace Paperworks {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader();

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_Renderer;
	};
}