#include "pwpch.h"

#include "OpenGLShader.h"
#include "Paperworks/Util/FileIO.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Paperworks {
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;

		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		if (type == "geometry")
			return GL_GEOMETRY_SHADER;

		PW_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& path)
		: m_RendererID(0)
	{
		std::string source = FileIO::ReadFile(path);
		auto shaders = PreProcess(source);
		Compile(shaders);
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
		: m_RendererID(0)
	{
		std::unordered_map<GLenum, std::string> shaders;

		shaders[GL_VERTEX_SHADER] = vertexSource;
		shaders[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(shaders);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) PW_CORE_ERROR("Error uploading uniform int to shader: {0} doesn't exist!", name);
		glUniform1i(location, value);
	}
	
	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) PW_CORE_ERROR("Error uploading uniform float to shader: {0} doesn't exist!", name);
		glUniform1f(location, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) PW_CORE_ERROR("Error uploading uniform float2 to shader: {0} doesn't exist!", name);
		glUniform2f(location, vec.x, vec.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) PW_CORE_ERROR("Error uploading uniform float3 to shader: {0} doesn't exist!", name);
		glUniform3f(location, vec.x, vec.y, vec.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) PW_CORE_ERROR("Error uploading uniform float4 to shader: {0} doesn't exist!", name);
		glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	}

	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) PW_CORE_ERROR("Error uploading uniform mat3 to shader: {0} doesn't exist!", name);
		glUniformMatrix3fv(location, 1, false, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) PW_CORE_ERROR("Error uploading uniform mat4 to shader: {0} doesn't exist!", name);
		glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& src)
	{
		std::unordered_map<GLenum, std::string> shaderMap;

		const char* typeIndicator = "#type";
		size_t typeLength = strlen(typeIndicator);
		size_t pos = src.find(typeIndicator);
		while (pos != std::string::npos) {
			size_t eol = src.find_first_of("\r\n", pos);
			PW_CORE_ASSERT(eol != std::string::npos, "Syntax Error!");
			size_t shaderBegin = pos + typeLength + 1;
			std::string shaderType = src.substr(shaderBegin, eol - shaderBegin);
			PW_CORE_ASSERT(ShaderTypeFromString(shaderType), "Ivalid shader type specified");

			size_t nextLinePos = src.find_first_not_of("\r\n", eol);
			PW_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = src.find(typeIndicator, nextLinePos);

			shaderMap[ShaderTypeFromString(shaderType)] = (pos == std::string::npos) ? src.substr(nextLinePos) : src.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderMap;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaders)
	{
		GLuint program = glCreateProgram();
		std::array<GLenum, 2> glShaderIDs;
		int i = 0;
		for (auto& key : shaders) {
			GLenum type = key.first;
			const std::string& source = key.second;

			GLuint shader = glCreateShader(type);
			const GLchar* shaderSrc = source.c_str();

			glShaderSource(shader, 1, &shaderSrc, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				PW_CORE_ERROR("{0}", infoLog.data());
				PW_CORE_ASSERT(false, "Shader compiliation failed!");

				break;
			}

			// Attach our shaders to our program
			glAttachShader(program, shader);
			glShaderIDs[i++] = shader;
		}

		m_RendererID = program;

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto shader : glShaderIDs) {
				glDeleteShader(shader);
			}

			PW_CORE_ERROR("{0}", infoLog.data());
			PW_CORE_ASSERT(false, "Shader linking failed!");

			return;
		}

		// Always detach shaders after a successful link.
		for (auto shader : glShaderIDs) {
			glDetachShader(program, shader);
			glDeleteShader(shader);
		}
	}
}
