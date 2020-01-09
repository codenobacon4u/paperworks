#pragma once

#include "Paperworks/Graphics/API/VertexArray.h"

#include <glad/glad.h>

namespace Paperworks {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Shared<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Shared<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Shared<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Shared<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

		static GLenum ShaderDataToOpenGL(ShaderDataType type);
	private:
		uint32_t m_RendererID;
		std::vector<Shared<VertexBuffer>> m_VertexBuffers;
		Shared<IndexBuffer> m_IndexBuffer;
	};
}