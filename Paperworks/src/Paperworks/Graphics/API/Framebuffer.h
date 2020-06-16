#pragma once

#include "Paperworks/Core/Core.h"

namespace Paperworks {

	struct FramebufferSpec {
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
		
		FramebufferSpec();
		FramebufferSpec(uint32_t width, uint32_t height)
			: Width(width), Height(height)
		{};
	};

	class Framebuffer {
	public:
		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetID() const = 0;
		virtual uint32_t GetColorAttachmentID() const = 0;

		virtual const FramebufferSpec& GetSpec() const = 0;

		static Shared<Framebuffer> Create(const FramebufferSpec& spec);
	};
}