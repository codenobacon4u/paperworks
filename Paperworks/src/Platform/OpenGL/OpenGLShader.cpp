#include "pwpch.h"

#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Paperworks {

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
		: m_Renderer(0)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			PW_CORE_ERROR("{0}", infoLog.data());
			PW_CORE_ASSERT(false, "Vertex shader compiliation failed!");

			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			PW_CORE_ERROR("{0}", infoLog.data());
			PW_CORE_ASSERT(false, "Fragment shader compiliation failed!");

			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_Renderer = glCreateProgram();
		GLuint program = m_Renderer;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)& isLinked);
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
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			PW_CORE_ERROR(infoLog.data());
			PW_CORE_ASSERT(false, "Shader linking failed!");

			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_Renderer);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_Renderer, name.c_str());
		if (location == -1) PW_CORE_ERROR("Error uploading uniform float to shader: {0} doesn't exist!", name);
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vec)
	{
		GLint location = glGetUniformLocation(m_Renderer, name.c_str());
		if (location == -1) PW_CORE_ERROR("Error uploading uniform float2 to shader: {0} doesn't exist!", name);
		glUniform2f(location, vec.x, vec.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vec)
	{
		GLint location = glGetUniformLocation(m_Renderer, name.c_str());
		if (location == -1) PW_CORE_ERROR("Error uploading uniform float3 to shader: {0} doesn't exist!", name);
		glUniform3f(location, vec.x, vec.y, vec.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vec)
	{
		GLint location = glGetUniformLocation(m_Renderer, name.c_str());
		if (location == -1) PW_CORE_ERROR("Error uploading uniform float4 to shader: {0} doesn't exist!", name);
		glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_Renderer, name.c_str());
		if (location == -1) PW_CORE_ERROR("Error uploading uniform mat3 to shader: {0} doesn't exist!", name);
		glUniformMatrix3fv(location, 1, false, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_Renderer, name.c_str());
		if (location == -1) PW_CORE_ERROR("Error uploading uniform mat4 to shader: {0} doesn't exist!", name);
		glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_Renderer);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}
}
