#include "pwpch.h"
#include "Renderer.h"

namespace Paperworks {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::Begin()
	{
	}

	void Renderer::Begin(Camera& camera)
	{
		s_SceneData->Projection = camera.GetProjectionMatrix();
		s_SceneData->View = camera.GetViewMatrix();
	}

	void Renderer::End()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_MVP.proj", s_SceneData->Projection);
		shader->UploadUniformMat4("u_MVP.view", s_SceneData->View);
		vertexArray->Bind();
		RenderCmd::DrawIndexed(vertexArray);
	}
}