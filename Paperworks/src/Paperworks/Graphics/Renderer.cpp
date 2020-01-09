#include "pwpch.h"
#include "Renderer.h"
#include "Renderer2D.h"

namespace Paperworks {

	Unique<Renderer::SceneData> Renderer::s_SceneData = CreateUnique<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCmd::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

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

	void Renderer::WindowResized(uint32_t width, uint32_t height)
	{
		RenderCmd::SetViewport(0, 0, width, height);
	}

	void Renderer::Submit(const Shared<VertexArray>& vertexArray, const Shared<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_MVP.proj", s_SceneData->Projection);
		shader->SetMat4("u_MVP.view", s_SceneData->View);
		shader->SetMat4("u_MVP.modl", transform);
		vertexArray->Bind();
		RenderCmd::DrawIndexed(vertexArray);
	}
}