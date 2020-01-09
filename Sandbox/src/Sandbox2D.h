#pragma once

#include "Paperworks.h"

#include <map>

class Sandbox2D : public Paperworks::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Paperworks::Time ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Paperworks::Event& event) override;

private:
	Paperworks::CameraController m_CameraController;

	std::map<std::string, Paperworks::Shared<Paperworks::Texture2D>> m_Textures;
};

