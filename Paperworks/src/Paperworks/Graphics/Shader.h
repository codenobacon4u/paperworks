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

		virtual void SetInt(const std::string& name, int value) = 0;

		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& vec) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& vec) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& vec) = 0;

		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shared<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);
		static Shared<Shader> Create(const std::string& path);
	};
}