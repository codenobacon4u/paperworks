#include "pwpch.h"
#include "Application.h"
#include "Input.h"
#include "Util/FileIO.h"

#include "Paperworks/Graphics/Renderer.h"

#include <glm\ext\matrix_transform.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include <GLFW\glfw3.h>

namespace Paperworks {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	
	Application::Application()
		: m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		PW_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	/*----------------------------Triangle VBO/VAO---------------------------*/
		m_VertexArray.reset(VertexArray::Create());

		// Setup Triangle Vertex Buffer Object
		float vertices[3 * 7] = {
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		std::shared_ptr<VertexBuffer> triVBO;
		triVBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		};
		triVBO->SetLayout(layout);
		// Add Triangle Vertex Buffer Object to Vertex Array
		m_VertexArray->AddVertexBuffer(triVBO);

		// Setup Triangle Index Buffer
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> triIB;
		triIB.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		// Set Index Buffer to Vertex Array
		m_VertexArray->SetIndexBuffer(triIB);

	/*-----------------------------Square VBO/VAO----------------------------*/
		m_SquareVA.reset(VertexArray::Create());

		// Setup Square Vertex Buffer Object
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
		std::shared_ptr<VertexBuffer> sqrVBO;
		sqrVBO.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		sqrVBO->SetLayout({
			{ShaderDataType::Float3, "a_Position"}
		});
		// Add Square Vertex Buffer Object to Vertex Array
		m_SquareVA->AddVertexBuffer(sqrVBO);

		// Setup Square Index Buffer
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> sqrIB;
		sqrIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		// Set Index Buffer to Vertex Array
		m_SquareVA->SetIndexBuffer(sqrIB);

		std::string baseVertSrc = FileIO::ReadFile("Shaders/base.vert");
		std::string baseFragSrc = FileIO::ReadFile("Shaders/base.frag");
		
		m_Shader.reset(new Shader(baseVertSrc, baseFragSrc));

		std::string blueVertSrc = FileIO::ReadFile("Shaders/blue.vert");
		std::string blueFragSrc = FileIO::ReadFile("Shaders/blue.frag");

		m_BlueShader.reset(new Shader(blueVertSrc, blueFragSrc));
	}


	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled) break;
		}
	}

	glm::vec2 cPos = glm::vec2(0, 0);
	float rot = 0.0f;

	void Application::Run() {
		while (m_Running)
		{
			if (Input::IsKeyPressed(GLFW_KEY_S))
				cPos.y -= 0.001f;
			else if (Input::IsKeyPressed(GLFW_KEY_W))
				cPos.y += 0.001f;
			if (Input::IsKeyPressed(GLFW_KEY_A))
				cPos.x -= 0.001f;
			else if (Input::IsKeyPressed(GLFW_KEY_D))
				cPos.x += 0.001f;
			if (Input::IsKeyPressed(GLFW_KEY_Q))
				rot ++;
			else if (Input::IsKeyPressed(GLFW_KEY_E))
				rot --;
			m_Camera.SetPosition(glm::vec3(cPos, 0.f));
			m_Camera.SetRotation(rot);
			RenderCmd::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
			RenderCmd::Clear();
			RenderCmd::SetViewport(m_Window->GetWidth(), m_Window->GetHeight());

			Renderer::Begin(m_Camera);
			
			Renderer::Submit(m_SquareVA, m_BlueShader);
			Renderer::Submit(m_VertexArray, m_Shader);

			Renderer::End();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
			
			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}