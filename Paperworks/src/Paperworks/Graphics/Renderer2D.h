#pragma once

#include "Paperworks/Graphics/Camera.h"

#include "Paperworks/Graphics/Texture.h"

namespace Paperworks {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void Begin(const Camera& camera);
		static void End();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<Texture2D>& texture);
	};
}