#pragma once

namespace Paperworks {
	class Context {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Unique<Context> Create(void* window);
	};
}
