#pragma once

#include "Paperworks/Graphics/API/Framebuffer.h"

namespace Paperworks {
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpec& spec);
		virtual ~OpenGLFramebuffer();

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetID() const override { return m_RendererID; };
		virtual uint32_t GetColorAttachmentID() const override { return m_ColorAttachment; };

		virtual const FramebufferSpec& GetSpec() const override { return m_Spec; };
	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
		FramebufferSpec m_Spec;
	};
}