#include "pwpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "examples\imgui_impl_glfw.h"
#include "examples\imgui_impl_opengl3.h"

#include "Paperworks\Application.h"

#include <GLFW\glfw3.h>
#include <glad\glad.h>

namespace Paperworks {
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{

	}


	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
		//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
		io.IniFilename = nullptr;

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin() 
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	
	void ImGuiLayer::End() 
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	static bool showDemo = true;
	static bool showPerform = true;
	void ImGuiLayer::OnImGuiRender()
	{
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::BeginMenu("New")) {
					if (ImGui::MenuItem("GameObject")) PW_CORE_INFO("Created new Game Object!");
					if (ImGui::MenuItem("Script")) PW_CORE_INFO("Created new Script!");
					ImGui::EndMenu();
				}
				if (ImGui::MenuItem("Exit", "Alt + F4")) Application::Get().Close();
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit")) {
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Tools")) {
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
}