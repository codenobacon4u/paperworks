#include "pwpch.h"

#include "Renderer2D.h"
#include "Shader.h"
#include "API/RenderCmd.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Paperworks {

	struct Storage2D {
		Shared<VertexArray> QuadVertexArray;
		Shared<Shader> TextureShader;
		Shared<Texture2D> Texture;
	};

	static Storage2D* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Storage2D();
		s_Data->QuadVertexArray = VertexArray::Create();

		float vertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Shared<VertexBuffer> vbo = VertexBuffer::Create(vertices, sizeof(vertices));
		vbo->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
			});
		s_Data->QuadVertexArray->AddVertexBuffer(vbo);

		uint32_t indicies[6] = { 0, 1, 2, 2, 3, 0 };
		Shared<IndexBuffer> ib = IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t));
		s_Data->QuadVertexArray->SetIndexBuffer(ib);

		s_Data->Texture = Texture2D::Create(1, 1);
		uint32_t tex = 0xffffffff;
		s_Data->Texture->SetData(&tex, sizeof(uint32_t));

		s_Data->TextureShader = Shader::Create("assets/shaders/textured.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);

	}
	
	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}
	
	void Renderer2D::Begin(const Camera& camera)
	{
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_MVP.proj", camera.GetProjectionMatrix());
		s_Data->TextureShader->SetMat4("u_MVP.view", camera.GetViewMatrix());
	}
	
	void Renderer2D::End()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->Texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_MVP.modl", transform);
		s_Data->QuadVertexArray->Bind();

		RenderCmd::DrawIndexed(s_Data->QuadVertexArray);
	}
	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}
	
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<Texture2D>& texture)
	{
		s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_MVP.modl", transform);
		s_Data->QuadVertexArray->Bind();

		RenderCmd::DrawIndexed(s_Data->QuadVertexArray);
	}
}