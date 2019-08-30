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
		virtual ~Shader() {}

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
	};
}