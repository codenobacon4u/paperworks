#pragma once

#include "Paperworks/Graphics/API/RenderPass.h"

namespace Paperworks {
	class OpenGLRenderPass : public RenderPass
	{
	public:
		OpenGLRenderPass();

		void Begin(glm::vec4 clearColor);
		void End();
	private:
		
	};
}