#pragma once

#include "ILogger.h"
#include "LogLevel.h"
#include <memory>
#include <format>

namespace Eflat 
{
	class Log {
	public:
		static void SetLogger(std::unique_ptr<ILogger> logger);
		static ILogger* Get();

        template<typename... Args>
        static void Trace(std::string_view fmt, Args&&... args) {
            LogImpl(LogLevel::Trace, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Debug(std::string_view fmt, Args&&... args) {
            LogImpl(LogLevel::Debug, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Info(std::string_view fmt, Args&&... args) {
            LogImpl(LogLevel::Info, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Warn(std::string_view fmt, Args&&... args) {
            LogImpl(LogLevel::Warning, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Error(std::string_view fmt, Args&&... args) {
            LogImpl(LogLevel::Error, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Fatal(std::string_view fmt, Args&&... args) {
            LogImpl(LogLevel::Fatal, fmt, std::forward<Args>(args)...);
        }

	private:
        static void SubmitLog(LogLevel level, std::string_view fmt, std::format_args args);

        template<typename... Args>
        static void LogImpl(LogLevel level, std::string_view fmt, Args&&... args) {
            SubmitLog(level, fmt, std::make_format_args(args...));
        }
	};
}

#ifndef EF_LOG
#define EF_LOG 1
#define EF_LOG_TRACE(...) ::Eflat::Log::Trace("[{}:{} {}] ", __FILE__, __LINE__, __func__), ::Eflat::Log::Trace(__VA_ARGS__)
#define EF_LOG_DEBUG(...) ::Eflat::Log::Debug("[{}:{} {}] ", __FILE__, __LINE__, __func__), ::Eflat::Log::Debug(__VA_ARGS__)
#define EF_LOG_INFO(...)  ::Eflat::Log::Info("[{}:{} {}] ", __FILE__, __LINE__, __func__),  ::Eflat::Log::Info(__VA_ARGS__)
#define EF_LOG_WARN(...)  ::Eflat::Log::Warn("[{}:{} {}] ", __FILE__, __LINE__, __func__),  ::Eflat::Log::Warn(__VA_ARGS__)
#define EF_LOG_ERROR(...) ::Eflat::Log::Error("[{}:{} {}] ", __FILE__, __LINE__, __func__), ::Eflat::Log::Error(__VA_ARGS__)
#define EF_LOG_FATAL(...) ::Eflat::Log::Fatal("[{}:{} {}] ", __FILE__, __LINE__, __func__), ::Eflat::Log::Fatal(__VA_ARGS__)
#endif // !EF_LOG