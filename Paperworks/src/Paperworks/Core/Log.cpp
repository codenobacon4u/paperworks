#include "pwpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_sinks.h"

namespace Paperworks {

	Shared<spdlog::logger> Log::s_CoreLogger;
	Shared<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("PAPERWORKS");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}