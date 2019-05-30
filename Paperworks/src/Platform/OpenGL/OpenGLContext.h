#pragma once
#include "Paperworks/Graphics/Context.h"

struct GLFWwindow;

namespace Paperworks {
	class OpenGLContext : public Context {
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_Window;
	};
}