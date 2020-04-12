#include "pwpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Paperworks {
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window)
	{
		PW_CORE_ASSERT(window, "Window handle is null!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PW_CORE_ASSERT(status, "Failed to initialize Glad!");

		PW_CORE_INFO("API:      OpenGL");
		PW_CORE_INFO("Version:  {0}", glGetString(GL_VERSION));
		PW_CORE_INFO("Graphics: {0}", glGetString(GL_RENDERER));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_Window);
	}
}