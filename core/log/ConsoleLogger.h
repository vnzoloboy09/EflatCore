#pragma once

#include "ILogger.h"
#include <mutex>

namespace Eflat
{
    class ConsoleLogger : public ILogger {
    public:
        ConsoleLogger();
        ~ConsoleLogger() override = default;

        void Log(LogLevel level, std::string_view message) override;
        void Flush() override;
        bool ShouldLog(LogLevel level) const override;

    private:
        void SetColor(LogLevel level);
        void ResetColor();
        std::string GetTimestamp() const;
        std::string_view GetLevelName(LogLevel level) const;

        std::mutex m_Mutex;
    };

}