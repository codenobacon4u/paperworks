#pragma once

#include "Paperworks/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Paperworks {
	class PAPERWORKS_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define PW_CORE_TRACE(...) ::Paperworks::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PW_CORE_INFO(...) ::Paperworks::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PW_CORE_WARN(...) ::Paperworks::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PW_CORE_ERROR(...) ::Paperworks::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PW_CORE_FATAL(...) ::Paperworks::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define PW_TRACE(...) ::Paperworks::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PW_INFO(...) ::Paperworks::Log::GetClientLogger()->info(__VA_ARGS__)
#define PW_WARN(...) ::Paperworks::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PW_ERROR(...) ::Paperworks::Log::GetClientLogger()->error(__VA_ARGS__)
#define PW_FATAL(...) ::Paperworks::Log::GetClientLogger()->fatal(__VA_ARGS__)