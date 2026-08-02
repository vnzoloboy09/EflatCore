#pragma once

#include "LogLevel.h"
#include <string_view>

namespace Eflat
{
	class ILogger {
	public:
		virtual ~ILogger() = default;

		virtual void Log(LogLevel level, std::string_view message) = 0;
		virtual void Flush() = 0;
		virtual bool ShouldLog(LogLevel) const = 0;
	};
}

