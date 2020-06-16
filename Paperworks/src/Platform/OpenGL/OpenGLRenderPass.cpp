#include "pwpch.h"
#include "OpenGLRenderPass.h"

#include <glad/glad.h>

namespace Paperworks {
	void OpenGLRenderPass::Begin(glm::vec4 clearColor)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, GetFramebuffer()->GetID());
		glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}