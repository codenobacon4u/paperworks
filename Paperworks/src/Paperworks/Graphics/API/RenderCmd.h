#pragma once

#include "RendererAPI.h"

namespace Paperworks {

	class RenderCmd
	{
	public:
		inline static void Init() { s_API->Init(); }

		static void SetClearColor(const glm::vec4& color) { s_API->SetClearColor(color); }
		static void Clear() { s_API->Clear(); }
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_API->SetViewport(x, y, width, height); }
		static std::pair<int, int> GetViewport() { return s_API->GetViewport(); }
		static void DrawIndexed(const Shared<VertexArray>& vertexArray, uint32_t indexCount = 0) { s_API->DrawIndexed(vertexArray, indexCount); }
	private:
		static RendererAPI* s_API;
	};
}