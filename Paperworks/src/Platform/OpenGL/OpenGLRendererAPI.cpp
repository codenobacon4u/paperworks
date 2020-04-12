#include "pwpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Paperworks {

	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         PW_CORE_CRITICAL("{0} Source: {1}", message, source); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       PW_CORE_ERROR("{0} Source: {1}", message, source); return;
		case GL_DEBUG_SEVERITY_LOW:          PW_CORE_WARN("{0} Source: {1}", message, source); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: PW_CORE_TRACE(message); return;
		}

		PW_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRendererAPI::Init()
	{
#ifdef PW_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	std::pair<int, int> OpenGLRendererAPI::GetViewport()
	{
		int viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		return std::pair<int, int>(viewport[2], viewport[3]);
	}

	void OpenGLRendererAPI::DrawIndexed(const Shared<VertexArray>& vertexArray, uint32_t indexCount)
	{
		glDrawElements(GL_TRIANGLES, indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}