#pragma once

#include "Paperworks/Graphics/API/RendererAPI.h"

namespace Paperworks {
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void SetViewport(unsigned int width, unsigned int height) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}