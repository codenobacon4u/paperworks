#pragma once

#ifdef PW_ENABLE_ASSERTS
	#define PW_ASSERT(x, ...) { if(!(x)) { PW_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PW_CORE_ASSERT(x, ...) { if(!(x)) { PW_CORE_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PW_ASSERT(x, ...)
	#define PW_CORE_ASSERT(x, ...)
#endif // PW_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define PW_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)