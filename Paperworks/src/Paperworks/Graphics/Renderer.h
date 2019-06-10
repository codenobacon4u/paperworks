#pragma once

namespace Paperworks {
	enum class API {
		None = 0, OpenGL = 1
	};
	class Renderer {
	public:
		inline static API GetAPI() { return m_API; }
	private:
		static API m_API;
	};
}