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
		static void Present();
		
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation = 0.0f, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation = 0.0f, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Shared<Texture2D>& texture, float rotation = 0.0f, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Shared<Texture2D>& texture, float rotation = 0.0f, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	};
}