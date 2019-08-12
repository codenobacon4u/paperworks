#pragma once

#include "RendererAPI.h"

namespace Paperworks {

	class RenderCmd
	{
	public:
		inline static void SetClearColor(const glm::vec4& color) { s_API->SetClearColor(color); }
		inline static void Clear() { s_API->Clear(); }
		inline static void SetViewport(unsigned int width, unsigned int height) { s_API->SetViewport(width, height); }

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { s_API->DrawIndexed(vertexArray); }
	private:
		static RendererAPI* s_API;
	};
}