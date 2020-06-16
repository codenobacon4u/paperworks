#pragma once

#include "Paperworks\Graphics\API\Framebuffer.h"

#include <glm/glm.hpp>

namespace Paperworks {
	class RenderPass 
	{
	public:
		virtual void Begin(glm::vec4 clearColor) = 0;
		virtual void End() = 0;

		Shared<Framebuffer> GetFramebuffer() const { return m_Framebuffer; };

		static Shared<RenderPass> Create();

	private:
		Shared<Framebuffer> m_Framebuffer;
	};
}