#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Paperworks {
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual std::pair<int, int> GetViewport() = 0;

		virtual void DrawIndexed(const Shared<VertexArray>& vertexArray, uint32_t indexCount) = 0;

		inline static API GetAPI() { return s_API; }
		static Unique<RendererAPI> Create();
	private:
		static API s_API;
	};
}