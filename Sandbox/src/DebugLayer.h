#pragma once

#include "Paperworks.h"

class DebugLayer : public Paperworks::Layer
{
public:
	DebugLayer();
	virtual ~DebugLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Paperworks::Time ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Paperworks::Event& event) override;
#if 1
private:
	glm::vec3 m_SquarePos;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	Paperworks::CameraController m_CameraController;

	Paperworks::Shared<Paperworks::Texture2D> m_SlimeTexture;
	
	Paperworks::Shared<Paperworks::Shader> m_Shader;
	Paperworks::Shared<Paperworks::Shader> m_BlueShader;
	Paperworks::Shared<Paperworks::Shader> m_TextureShader;
	
	Paperworks::Shared<Paperworks::VertexArray> m_TriangleVA;
	Paperworks::Shared<Paperworks::VertexArray> m_SquareVA;
#endif
};