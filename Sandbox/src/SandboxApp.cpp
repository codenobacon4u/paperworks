#include <Paperworks.h>
#include <glm/gtc/matrix_transform.hpp>
#include <ImGui/imgui.h>

#include <Platform/OpenGL/OpenGLShader.h>
#include <glm\glm\gtc\type_ptr.hpp>

class DebugLayer : public Paperworks::Layer
{
public:
	DebugLayer()
		: Layer("Debug"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CamPos(0.0f), m_SquarePos(0.0f)
	{
		/*----------------------------Triangle VBO/VAO---------------------------*/
		m_TriangleVA.reset(Paperworks::VertexArray::Create());

		// Setup Triangle Vertex Buffer Object
		float vertices[3 * 7] = {
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		std::shared_ptr<Paperworks::VertexBuffer> triVBO;
		triVBO.reset(Paperworks::VertexBuffer::Create(vertices, sizeof(vertices)));
		Paperworks::BufferLayout layout = {
			{Paperworks::ShaderDataType::Float3, "a_Position"},
			{Paperworks::ShaderDataType::Float4, "a_Color"}
		};
		triVBO->SetLayout(layout);
		// Add Triangle Vertex Buffer Object to Vertex Array
		m_TriangleVA->AddVertexBuffer(triVBO);

		// Setup Triangle Index Buffer
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Paperworks::IndexBuffer> triIB;
		triIB.reset(Paperworks::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		// Set Index Buffer to Vertex Array
		m_TriangleVA->SetIndexBuffer(triIB);

		/*-----------------------------Square VBO/VAO----------------------------*/
		m_SquareVA.reset(Paperworks::VertexArray::Create());

		// Setup Square Vertex Buffer Object
		float squareVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		std::shared_ptr<Paperworks::VertexBuffer> sqrVBO;
		sqrVBO.reset(Paperworks::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		sqrVBO->SetLayout({
			{Paperworks::ShaderDataType::Float3, "a_Position"},
			{Paperworks::ShaderDataType::Float2, "a_TexCoord"}
		});
		// Add Square Vertex Buffer Object to Vertex Array
		m_SquareVA->AddVertexBuffer(sqrVBO);

		// Setup Square Index Buffer
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Paperworks::IndexBuffer> sqrIB;
		sqrIB.reset(Paperworks::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		// Set Index Buffer to Vertex Array
		m_SquareVA->SetIndexBuffer(sqrIB);

		std::string baseVertSrc = Paperworks::FileIO::ReadFile("assets/shaders/base.vert");
		std::string baseFragSrc = Paperworks::FileIO::ReadFile("assets/shaders/base.frag");

		m_Shader.reset(Paperworks::Shader::Create(baseVertSrc, baseFragSrc));

		std::string blueVertSrc = Paperworks::FileIO::ReadFile("assets/shaders/blue.vert");
		std::string blueFragSrc = Paperworks::FileIO::ReadFile("assets/shaders/blue.frag");

		m_BlueShader.reset(Paperworks::Shader::Create(blueVertSrc, blueFragSrc));

		m_TextureShader.reset(Paperworks::Shader::Create("assets/shaders/textured.glsl"));

		m_SlimeTexture = Paperworks::Texture2D::Create("assets/textures/slime.png");

		std::dynamic_pointer_cast<Paperworks::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Paperworks::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Paperworks::Time ts) override
	{
		if (Paperworks::Input::IsKeyPressed(PW_KEY_LEFT))
			m_CamPos.x -= m_CamMoveSpeed * ts.DeltaTime();
		else if (Paperworks::Input::IsKeyPressed(PW_KEY_RIGHT))
			m_CamPos.x += m_CamMoveSpeed * ts.DeltaTime();

		if (Paperworks::Input::IsKeyPressed(PW_KEY_UP))
			m_CamPos.y += m_CamMoveSpeed * ts.DeltaTime();
		else if (Paperworks::Input::IsKeyPressed(PW_KEY_DOWN))
			m_CamPos.y -= m_CamMoveSpeed * ts.DeltaTime();

		if (Paperworks::Input::IsKeyPressed(PW_KEY_Q))
			m_CamRot += m_CamRotSpeed * ts.DeltaTime();
		else if (Paperworks::Input::IsKeyPressed(PW_KEY_E))
			m_CamRot -= m_CamRotSpeed * ts.DeltaTime();


		if (Paperworks::Input::IsKeyPressed(PW_KEY_A))
			m_SquarePos.x -= m_CamMoveSpeed * ts.DeltaTime();
		else if (Paperworks::Input::IsKeyPressed(PW_KEY_D))
			m_SquarePos.x += m_CamMoveSpeed * ts.DeltaTime();

		if (Paperworks::Input::IsKeyPressed(PW_KEY_W))
			m_SquarePos.y += m_CamMoveSpeed * ts.DeltaTime();
		else if (Paperworks::Input::IsKeyPressed(PW_KEY_S))
			m_SquarePos.y -= m_CamMoveSpeed * ts.DeltaTime();

		Paperworks::RenderCmd::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Paperworks::RenderCmd::Clear();
		Paperworks::RenderCmd::SetViewport(Paperworks::Application::Get().GetWindow().GetWidth(), Paperworks::Application::Get().GetWindow().GetHeight());

		m_Camera.SetPosition(m_CamPos);
		m_Camera.SetRotation(m_CamRot);

		Paperworks::Renderer::Begin(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_BlueShader->Bind();
		m_BlueShader->UploadUniformFloat3("u_Color", m_SquareColor);
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Paperworks::Renderer::Submit(m_SquareVA, m_BlueShader, transform);
			}
		}

		m_SlimeTexture->Bind();
		Paperworks::Renderer::Submit(m_SquareVA, m_TextureShader, glm::translate(glm::mat4(1.0f), glm::vec3(m_SquarePos.x, m_SquarePos.y, 1.0f)));
		
		Paperworks::Renderer::Submit(m_TriangleVA, m_Shader);

		Paperworks::Renderer::End();
	}

	
	virtual void OnImGuiRender()
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
				if (ImGui::MenuItem("Reset Camera")) m_CamPos = glm::vec3(0.0f);
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

		if (showColor) {
			ImGui::Begin("Color Shader Settings");
			ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
			ImGui::End();
		}
	}

	void OnEvent(Paperworks::Event& event) override
	{
		
	}

private:
	glm::vec3 m_SquarePos;

	glm::vec3 m_CamPos;
	float m_CamMoveSpeed = 5.0f;

	float m_CamRot = 0.0f;
	float m_CamRotSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	Paperworks::Camera m_Camera;

	std::shared_ptr<Paperworks::Texture2D> m_SlimeTexture;

	std::shared_ptr<Paperworks::Shader> m_Shader;
	std::shared_ptr<Paperworks::Shader> m_BlueShader;
	std::shared_ptr<Paperworks::Shader> m_TextureShader;

	std::shared_ptr<Paperworks::VertexArray> m_TriangleVA;
	std::shared_ptr<Paperworks::VertexArray> m_SquareVA;
};

class Sandbox : public Paperworks::Application
{
public:
	Sandbox() {
		PushLayer(new DebugLayer());
	}

	~Sandbox() {

	}
};

Paperworks::Application* Paperworks::CreateApplication() {
	return new Sandbox();
}