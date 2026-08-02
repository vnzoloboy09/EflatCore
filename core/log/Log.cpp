#include "Log.h"
#include "ConsoleLogger.h"
#include <string>

namespace Eflat 
{
    static std::unique_ptr<ILogger> s_Logger = std::make_unique<ConsoleLogger>();

    void Log::SetLogger(std::unique_ptr<ILogger> logger) {
        s_Logger = std::move(logger);
    }

    ILogger* Log::Get() {
        return s_Logger.get();
    }

    void Log::SubmitLog(LogLevel level, std::string_view fmt, std::format_args args) {
        if (!s_Logger || !s_Logger->ShouldLog(level)) {
            return;
        }

        std::string formatted_message = std::vformat(fmt, args);
        s_Logger->Log(level, formatted_message);
    }

}