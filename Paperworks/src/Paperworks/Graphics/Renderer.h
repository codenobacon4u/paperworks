#pragma once

#include "API/RenderCmd.h"
#include "Paperworks\Graphics\Shader.h"
#include "Paperworks\Graphics\Camera.h"

namespace Paperworks {

	class Renderer 
	{
	public:
		static void Begin();
		static void Begin(Camera& camera);
		static void End();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 Projection;
			glm::mat4 View;
		};

		static SceneData* s_SceneData;
	};
}