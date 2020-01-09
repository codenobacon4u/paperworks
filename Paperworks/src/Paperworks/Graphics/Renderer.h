#pragma once

#include "API/RenderCmd.h"
#include "Paperworks/Graphics/Shader.h"
#include "Paperworks/Graphics/Camera.h"

namespace Paperworks {

	class Renderer 
	{
	public:
		static void Init();
		static void Shutdown();

		static void Begin();
		static void Begin(Camera& camera);
		static void End();

		static void WindowResized(uint32_t width, uint32_t height);

		static void Submit(const Shared<VertexArray>& vertexArray, const Shared<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 Projection;
			glm::mat4 View;
		};

		static Unique<SceneData> s_SceneData;
	};
}