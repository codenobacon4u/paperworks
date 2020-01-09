#pragma once

#include <memory>

#ifdef _WIN32
	#define PW_PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define PW_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define PW_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define PW_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define PW_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

#ifdef PW_DEBUG
	#define PW_ENABLE_ASSERTS
#endif

#ifdef PW_ENABLE_ASSERTS
	#define PW_ASSERT(x, ...) { if(!(x)) { PW_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PW_CORE_ASSERT(x, ...) { if(!(x)) { PW_CORE_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PW_ASSERT(x, ...)
	#define PW_CORE_ASSERT(x, ...)
#endif // PW_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define PW_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Paperworks {
	
	template<typename T>
	using Unique = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Unique<T> CreateUnique(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Shared = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Shared<T> CreateShared(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}