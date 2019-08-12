#include "pwpch.h"
#include "RenderCmd.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Paperworks {
	RendererAPI* RenderCmd::s_API = new OpenGLRendererAPI;
}