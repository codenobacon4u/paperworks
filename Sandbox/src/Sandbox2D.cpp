#include "Sandbox2D.h"

#include <ImGui/imgui.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_Textures["Slime"] = Paperworks::Texture2D::Create("assets/textures/slime.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Paperworks::Time ts)
{
	m_CameraController.OnUpdate(ts);

	Paperworks::RenderCmd::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Paperworks::RenderCmd::Clear();

	Paperworks::Renderer2D::Begin(m_CameraController.GetCamera());

	Paperworks::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Paperworks::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Paperworks::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Textures["Slime"]);

	Paperworks::Renderer2D::End();
}

void Sandbox2D::OnImGuiRender()
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
}

void Sandbox2D::OnEvent(Paperworks::Event& event)
{
	m_CameraController.OnEvent(event);
}
