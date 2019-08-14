#include <Paperworks.h>

class DebugLayer : public Paperworks::Layer
{
public:
	DebugLayer()
		: Layer("Debug"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CamPos(0.0f)
	{
		/*----------------------------Triangle VBO/VAO---------------------------*/
		m_VertexArray.reset(Paperworks::VertexArray::Create());

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
		m_VertexArray->AddVertexBuffer(triVBO);

		// Setup Triangle Index Buffer
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Paperworks::IndexBuffer> triIB;
		triIB.reset(Paperworks::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		// Set Index Buffer to Vertex Array
		m_VertexArray->SetIndexBuffer(triIB);

		/*-----------------------------Square VBO/VAO----------------------------*/
		m_SquareVA.reset(Paperworks::VertexArray::Create());

		// Setup Square Vertex Buffer Object
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
		std::shared_ptr<Paperworks::VertexBuffer> sqrVBO;
		sqrVBO.reset(Paperworks::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		sqrVBO->SetLayout({
			{Paperworks::ShaderDataType::Float3, "a_Position"}
		});
		// Add Square Vertex Buffer Object to Vertex Array
		m_SquareVA->AddVertexBuffer(sqrVBO);

		// Setup Square Index Buffer
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Paperworks::IndexBuffer> sqrIB;
		sqrIB.reset(Paperworks::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		// Set Index Buffer to Vertex Array
		m_SquareVA->SetIndexBuffer(sqrIB);

		std::string baseVertSrc = Paperworks::FileIO::ReadFile("Shaders/base.vert");
		std::string baseFragSrc = Paperworks::FileIO::ReadFile("Shaders/base.frag");

		m_Shader.reset(new Paperworks::Shader(baseVertSrc, baseFragSrc));

		std::string blueVertSrc = Paperworks::FileIO::ReadFile("Shaders/blue.vert");
		std::string blueFragSrc = Paperworks::FileIO::ReadFile("Shaders/blue.frag");

		m_BlueShader.reset(new Paperworks::Shader(blueVertSrc, blueFragSrc));
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

		Paperworks::RenderCmd::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Paperworks::RenderCmd::Clear();
		Paperworks::RenderCmd::SetViewport(Paperworks::Application::Get().GetWindow().GetWidth(), Paperworks::Application::Get().GetWindow().GetHeight());

		m_Camera.SetPosition(m_CamPos);
		m_Camera.SetRotation(m_CamRot);

		Paperworks::Renderer::Begin(m_Camera);

		Paperworks::Renderer::Submit(m_SquareVA, m_BlueShader);
		Paperworks::Renderer::Submit(m_VertexArray, m_Shader);

		Paperworks::Renderer::End();
	}

	virtual void OnImGuiRender() 
	{

	}

	void OnEvent(Paperworks::Event& event) override
	{
		
	}

private:
	glm::vec3 m_CamPos;
	float m_CamMoveSpeed = 5.0f;

	float m_CamRot = 0.0f;
	float m_CamRotSpeed = 180.0f;

	Paperworks::Camera m_Camera;

	std::shared_ptr<Paperworks::Shader> m_Shader;
	std::shared_ptr<Paperworks::VertexArray> m_VertexArray;

	std::shared_ptr<Paperworks::Shader> m_BlueShader;
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