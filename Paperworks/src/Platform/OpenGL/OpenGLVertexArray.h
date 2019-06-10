#pragma once

#include "Paperworks/Graphics/API/VertexArray.h"

#include <glad/glad.h>

namespace Paperworks {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray(BufferLayout layout);
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		static GLenum ShaderDataToOpenGL(ShaderDataType type);
	private:
		uint32_t m_RendererID;
	};
}