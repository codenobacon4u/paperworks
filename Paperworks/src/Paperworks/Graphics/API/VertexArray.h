#pragma once

#include "Buffer.h"

namespace Paperworks {

	class VertexArray
	{
	public:
		VertexArray() = default;
		
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexArray* Create(BufferLayout layout);
	};
}