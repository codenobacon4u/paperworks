#pragma once

#include "Paperworks.h"

#include <map>

class EditorLayer : public Paperworks::Layer
{
#define LENGTH 100
#define WIDTH  100
public:
	EditorLayer();
	virtual ~EditorLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Paperworks::Time ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Paperworks::Event& event) override;

private:
	void RandomizeTiles();

	Paperworks::CameraController m_CameraController;
	std::map<std::string, Paperworks::Shared<Paperworks::Texture2D>> m_Textures;
	std::string m_MapTextures[10000];

	Paperworks::Shared<Paperworks::Framebuffer> m_Framebuffer;
	bool gameRunning;
};

