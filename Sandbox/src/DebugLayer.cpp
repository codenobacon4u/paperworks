#include "DebugLayer.h"

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

DebugLayer::DebugLayer()
	: Layer("Debug"), m_CameraController(1920.0f / 1080.0f), m_SquarePos(0.0f)
{
#if 1
	/*----------------------------Triangle VBO/VAO---------------------------*/
	m_TriangleVA = Paperworks::VertexArray::Create();

	// Setup Triangle Vertex Buffer Object
	float vertices[3 * 7] = {
		 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
	};
	Paperworks::Shared<Paperworks::VertexBuffer> triVBO = Paperworks::VertexBuffer::Create(vertices, sizeof(vertices));
	Paperworks::BufferLayout layout = {
		{Paperworks::ShaderDataType::Float3, "a_Position"},
		{Paperworks::ShaderDataType::Float4, "a_Color"}
	};
	triVBO->SetLayout(layout);
	// Add Triangle Vertex Buffer Object to Vertex Array
	m_TriangleVA->AddVertexBuffer(triVBO);

	// Setup Triangle Index Buffer
	uint32_t indices[3] = { 0, 1, 2 };
	Paperworks::Shared<Paperworks::IndexBuffer> triIB = Paperworks::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	// Set Index Buffer to Vertex Array
	m_TriangleVA->SetIndexBuffer(triIB);

	/*-----------------------------Square VBO/VAO----------------------------*/
	m_SquareVA = Paperworks::VertexArray::Create();

	// Setup Square Vertex Buffer Object
	float squareVertices[4 * 5] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	Paperworks::Shared<Paperworks::VertexBuffer> sqrVBO = Paperworks::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	sqrVBO->SetLayout({
		{Paperworks::ShaderDataType::Float3, "a_Position"},
		{Paperworks::ShaderDataType::Float2, "a_TexCoord"}
		});
	// Add Square Vertex Buffer Object to Vertex Array
	m_SquareVA->AddVertexBuffer(sqrVBO);

	// Setup Square Index Buffer
	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Paperworks::Shared<Paperworks::IndexBuffer> sqrIB = Paperworks::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	// Set Index Buffer to Vertex Array
	m_SquareVA->SetIndexBuffer(sqrIB);

	std::string baseVertSrc = Paperworks::FileIO::ReadFile("assets/shaders/base.vert");
	std::string baseFragSrc = Paperworks::FileIO::ReadFile("assets/shaders/base.frag");

	m_Shader = Paperworks::Shader::Create("base", baseVertSrc, baseFragSrc);

	m_TextureShader = Paperworks::Shader::Create("assets/shaders/textured-old.glsl");

	m_SlimeTexture = Paperworks::Texture2D::Create("assets/textures/slime.png");

	m_TextureShader->Bind();
	m_TextureShader->SetInt("u_Texture", 0);
#endif
}

void DebugLayer::OnAttach()
{
}

void DebugLayer::OnDetach()
{
}

void DebugLayer::OnUpdate(Paperworks::Time ts)
{
#if 1
	{ // Updates
		m_CameraController.OnUpdate(ts);
	}

	{ // Render Clear
		Paperworks::RenderCmd::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Paperworks::RenderCmd::Clear();
	}

	{ // Render Calls
		Paperworks::Renderer::Begin(m_CameraController.GetCamera());

		m_SlimeTexture->Bind();
		Paperworks::Renderer::Submit(m_SquareVA, m_TextureShader, glm::translate(glm::mat4(1.0f), glm::vec3(m_SquarePos.x, m_SquarePos.y, 1.0f)));
		Paperworks::Renderer::Submit(m_TriangleVA, m_Shader, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 1.0f)));

		Paperworks::Renderer::End();
	}
#endif
}


void DebugLayer::OnImGuiRender()
{
	static bool showDemo = false;
	static bool showColor = false;
	static bool showPerform = true;
	static bool vsync = false;
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::BeginMenu("New")) {
				if (ImGui::MenuItem("GameObject")) PW_CORE_INFO("Created new Game Object!");
				if (ImGui::MenuItem("Script")) PW_CORE_INFO("Created new Script!");
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Exit", "Alt + F4")) Paperworks::Application::Get().Close();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit")) {
			ImGui::MenuItem("Color Shader", "", &showColor);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Tools")) {
			ImGui::MenuItem("Enable VSync", "", &vsync);
			Paperworks::Application::Get().GetWindow().SetVSync(vsync);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View")) {
			ImGui::MenuItem("Demo ImGui Window", "", &showDemo);
			ImGui::MenuItem("Performance Window", "", &showPerform);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	if (showDemo)
		ImGui::ShowDemoWindow(&showDemo);

	if (showPerform) {
		ImGui::Begin("Performance");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
#if 1
	if (showColor) {
		ImGui::Begin("Color Shader Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
#endif
}

void DebugLayer::OnEvent(Paperworks::Event& event)
{
	m_CameraController.OnEvent(event);
}