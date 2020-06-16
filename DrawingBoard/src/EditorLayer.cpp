#include "EditorLayer.h"

#include <ImGui/imgui.h>
#include <glm\glm\gtc\type_ptr.hpp>

static int sprites = 0;

EditorLayer::EditorLayer()
	: Layer("EditorLayer"), m_CameraController(1920.0f / 1080.0f), gameRunning(false)
{
}

void EditorLayer::OnAttach()
{
	m_Textures["map"] = Paperworks::Texture2D::Create("assets/textures/map_tiles.png");
	m_Textures["slime"] = Paperworks::Texture2D::Create("assets/textures/slime.png");
	m_Textures["ground"] = Paperworks::Texture2D::Create("assets/textures/ground.png");
	m_Textures["sand"] = Paperworks::Texture2D::Create("assets/textures/sand.png");
	m_Textures["sky"] = Paperworks::Texture2D::Create("assets/textures/sky.png");
	m_Textures["brick2"] = Paperworks::Texture2D::Create("assets/textures/brick2.png");
	m_Textures["water1"] = Paperworks::Texture2D::Create("assets/textures/water1.png");

	m_Framebuffer = Paperworks::Framebuffer::Create(Paperworks::FramebufferSpec(1920,1080));

	RandomizeTiles();
}

void EditorLayer::OnDetach()
{
}

static glm::vec3 position = glm::vec3(0.0f);
static glm::vec2 size = glm::vec3(1.0f);
static glm::vec4 color = glm::vec4(1.0f);
static float tiling = 1.0f;
static glm::vec2 view = glm::vec2(1920.f, 1080.f);
static glm::vec2 oldView = glm::vec2(1920.f, 1080.f);

void EditorLayer::OnUpdate(Paperworks::Time ts)
{
	m_CameraController.OnUpdate(ts);


	Paperworks::Renderer2D::ResetStats();

	m_Framebuffer->Bind();

	Paperworks::RenderCmd::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f});
	Paperworks::RenderCmd::Clear();

	Paperworks::Renderer2D::Begin(m_CameraController.GetCamera());
	
	sprites = 0;
	for (uint32_t i = 0; i < LENGTH; i++) {
		for (uint32_t j = 0; j < WIDTH; j++) {
			Paperworks::Renderer2D::DrawQuad(position + glm::vec3(j, i, 0.0f), size, m_Textures[m_MapTextures[i * 23 + j]]);
			sprites++;
		}
	}

	Paperworks::Renderer2D::End();

	m_Framebuffer->Unbind();
}

void EditorLayer::OnImGuiRender()
{
	static float zoom = m_CameraController.GetZoom();
	static bool showDemo = false;
	static bool showColor = false;
	static bool showPerform = true;
	static bool vsync = false;
	auto stats = Paperworks::Renderer2D::GetStats();

	static bool dockingEnabled = true;
	if (dockingEnabled)
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);
				if (ImGui::MenuItem("Edit Color")) showColor = !showColor;
				if (ImGui::MenuItem("Exit")) Paperworks::Application::Get().Close();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		{
			ImGui::Begin("Game", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
			view = ImGui::GetWindowSize();
			if (view != oldView)
			{
				m_Framebuffer->Resize(view.x, view.y);
				oldView = view;
			}
			uint32_t textureID = m_Framebuffer->GetColorAttachmentID();
			ImGui::Image((void*)textureID, ImVec2{ view.x, view.y }, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::End();
		}
		ImGui::Begin("Application Stats");
		ImGui::Text("Resolution %d x %d", (int)view.x, (int)view.y);
		ImGui::Text("Application Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Sprites Rendered %d", sprites);
		ImGui::Text("Zoom %.2f", m_CameraController.GetZoom());
		ImGui::Separator();
		ImGui::Text("Renderer Stats");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Verties: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
		ImGui::Checkbox("Running", &gameRunning);
		ImGui::End();

		ImGui::End();
	}
	
	if (showColor) {
		ImGui::SetNextWindowSize(glm::vec2(300.0f, 500.0f), ImGuiCond_Once);
		ImGui::Begin("Edit Transform");
		ImGui::ColorPicker4("Tint", (float*)&color);
		ImGui::SliderFloat3("Position", (float*)&position, -10.0f, 10.0f);
		ImGui::SliderFloat2("Size", (float*)&size, 0.1f, 10.0f);
		ImGui::SliderFloat("Tiling", (float*)&tiling, 1.0f, 100.0f);
		if (ImGui::Button("Randomize Tiles")) { RandomizeTiles(); }
		ImGui::End();
	}
}

void EditorLayer::OnEvent(Paperworks::Event& event)
{
	m_CameraController.OnEvent(event);
}

void EditorLayer::RandomizeTiles()
{
	for (size_t i = 0; i < LENGTH; i++) {
		for (size_t j = 0; j < WIDTH; j++) {
			int random = rand() % 6 + 1;
			switch (random) {
			case 1:
				m_MapTextures[i * 23 + j] = "slime";
				break;
			case 2:
				m_MapTextures[i * 23 + j] = "ground";
				break;
			case 3:
				m_MapTextures[i * 23 + j] = "sand";
				break;
			case 4:
				m_MapTextures[i * 23 + j] = "sky";
				break;
			case 5:
				m_MapTextures[i * 23 + j] = "brick2";
				break;
			case 6:
				m_MapTextures[i * 23 + j] = "water1";
				break;
			}
		}
	}
}
