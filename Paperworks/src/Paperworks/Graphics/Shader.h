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
		virtual ~Shader() = default;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& vec) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& vec) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& vec) = 0;

		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual const std::string& GetName() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shared<Shader> Create(const std::string& path);
		static Shared<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
	};

	class ShaderLibrary {
	public:
		void Add(const std::string& name, const Shared<Shader>& shader);
		void Add(const Shared<Shader>& shader);

		Shared<Shader> Load(const std::string& filepath);
		Shared<Shader> Load(const std::string& name, const std::string& filepath);

		Shared<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Shared<Shader>> m_Shaders;
	};
}