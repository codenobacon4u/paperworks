#include "pwpch.h"

#include "Paperworks/Graphics/API/Buffer.h"
#include "Paperworks/Graphics/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Paperworks {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case API::None:
			return nullptr;
		case API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case API::None:
			return nullptr;
		case API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}
		return nullptr;
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
		: m_Elements(elements)
	{
		CalculateOffsetsAndStride();
	}

	void BufferLayout::CalculateOffsetsAndStride()
	{
		uint32_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements) {
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}
}
