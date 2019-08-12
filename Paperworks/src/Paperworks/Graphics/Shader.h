#pragma once

#include <string>
#include <glm/glm.hpp>

struct UBO {
	glm::mat4 proj;
	glm::mat4 view;
	glm::mat4 model;
};

namespace Paperworks {
	class Shader {
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_Renderer;
	};
}