#pragma once

#ifndef PE_DEBUG_GUARD
#define PE_DEBUG_GUARD

#include <string>

#include <Core/Config.hpp>

namespace Pe
{
	enum class LogLevel
	{
		Normal,
		Info,
		Warning,
		Error
	};

	namespace Debug
	{
		void Log(const std::string& _msg, LogLevel _level = LogLevel::Normal) noexcept;
		void Assert(bool predicate, const std::string& _msg, bool logOnSuccess = false);
	}

#if PE_LOG

	#define LOG(str, ...) Debug::Log(str, __VA_ARGS__)
	#define ASSERT(b, str, ...) Debug::Assert(b, str, __VA_ARGS__)

#else

	#define LOG(str, ...)
	#define ASSERT(b, str, ...)

#endif
}

#endif // GUARD