#include "Sandbox2D.h"

#include <ImGui/imgui.h>
#include <glm\glm\gtc\type_ptr.hpp>

static int sprites = 0;

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f), gameRunning(false)
{
}

void Sandbox2D::OnAttach()
{
	m_Textures["map"] = Paperworks::Texture2D::Create("assets/textures/map_tiles.png");
	m_Textures["slime"] = Paperworks::Texture2D::Create("assets/textures/slime.png");
	m_Textures["ground"] = Paperworks::Texture2D::Create("assets/textures/ground.png");
	m_Textures["sand"] = Paperworks::Texture2D::Create("assets/textures/sand.png");
	m_Textures["sky"] = Paperworks::Texture2D::Create("assets/textures/sky.png");
	m_Textures["brick2"] = Paperworks::Texture2D::Create("assets/textures/brick2.png");
	m_Textures["water1"] = Paperworks::Texture2D::Create("assets/textures/water1.png");

	Paperworks::FramebufferSpec spec;
	spec.Width = 1920;
	spec.Height = 1080;
	m_Framebuffer = Paperworks::Framebuffer::Create(spec);

	RandomizeTiles();
}

void Sandbox2D::OnDetach()
{
}

static glm::vec3 position = glm::vec3(0.0f);
static glm::vec2 size = glm::vec3(1.0f);
static glm::vec4 color = glm::vec4(1.0f);
static float tiling = 1.0f;
static glm::vec2 view = glm::vec2(1920.f, 1080.f);
static glm::vec2 oldView = glm::vec2(1920.f, 1080.f);

void Sandbox2D::OnUpdate(Paperworks::Time ts)
{
	m_CameraController.OnUpdate(ts);


	Paperworks::Renderer2D::ResetStats();

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
}

void Sandbox2D::OnImGuiRender()
{
	static float zoom = m_CameraController.GetZoom();
	static bool showDemo = false;
	static bool showColor = false;
	static bool showPerform = true;
	static bool vsync = false;
	auto stats = Paperworks::Renderer2D::GetStats();
	
	ImGui::Begin("Application Stats");
	ImGui::Text("Resolution %d x %d", view.x, view.y);
	ImGui::Text("Application Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Sprites Rendered %d", sprites);
	ImGui::Text("Zoom %.2f", m_CameraController.GetZoom());
	if (ImGui::SliderFloat("Zoom Level", &zoom, 0.25f, 100.0f))
		m_CameraController.SetZoom(zoom);
	ImGui::Separator();
	ImGui::Text("Renderer Stats");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Verties: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::End();
	
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

void Sandbox2D::OnEvent(Paperworks::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::RandomizeTiles()
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
