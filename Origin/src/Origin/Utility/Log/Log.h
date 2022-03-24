#pragma once

#include <memory>

#include "Origin/Core/Core.h"

#include "spdlog/spdlog.h"


namespace Origin {

	class ORIGIN_API Log {
	public:
		
		static void Init();

		inline static std::shared_ptr<spdlog::logger> getCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger> getClientLogger() { return s_ClientLogger; };


	private:

		inline static std::shared_ptr<spdlog::logger> s_CoreLogger;
		inline static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


#ifdef OG_CORE

	#define ORIGIN_TRACE(...) ::Origin::Log::getCoreLogger()->trace(__VA_ARGS__)
	#define ORIGIN_INFO(...) ::Origin::Log::getCoreLogger()->info(__VA_ARGS__)
	#define ORIGIN_WARN(...) ::Origin::Log::getCoreLogger()->warn(__VA_ARGS__)
	#define ORIGIN_ERROR(...) ::Origin::Log::getCoreLogger()->error(__VA_ARGS__)
	#define ORIGIN_CRITICAL(...) ::Origin::Log::getCoreLogger()->critical(__VA_ARGS__)
	
	#define ORIGIN_ASSERT(x, ...) if(!x) { ::Origin::Log::getCoreLogger()->error(__VA_ARGS__); __debugbreak(); }

#else


	#define ORIGIN_TRACE(...) ::Origin::Log::getClientLogger()->trace(__VA_ARGS__)
	#define ORIGIN_INFO(...) ::Origin::Log::getClientLogger()->info(__VA_ARGS__)
	#define ORIGIN_WARN(...) ::Origin::Log::getClientLogger()->warn(__VA_ARGS__)
	#define ORIGIN_ERROR(...) ::Origin::Log::getClientLogger()->error(__VA_ARGS__)
	#define ORIGIN_FATAL(...) ::Origin::Log::getClientLogger()->fatal(__VA_ARGS__)
	
	#define ORIGIN_ASSERT(x, ...) if(!x) { ::Origin::Log::getCoreLogger()->error(__VA_ARGS__); __debugbreak(); }

#endif 

