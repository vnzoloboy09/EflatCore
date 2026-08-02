#include "ConsoleLogger.h"
#include <iostream>
#include <chrono>
#include <format>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Eflat {

    ConsoleLogger::ConsoleLogger() = default;

    bool ConsoleLogger::ShouldLog(LogLevel level) const {
        return true; 
    }

    void ConsoleLogger::Log(LogLevel level, std::string_view message) {
        std::lock_guard<std::mutex> lock(m_Mutex);

        SetColor(level);

        std::cout << std::format("[{}] [{}] {}\n",
            GetLevelName(level),
            GetTimestamp(),
            message);

        ResetColor();
    }

    void ConsoleLogger::Flush() {
        std::lock_guard<std::mutex> lock(m_Mutex);
        std::cout << std::flush;
    }

    std::string ConsoleLogger::GetTimestamp() const {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        return std::format("{:%H:%M:%S}.{:03d}", now, ms.count());
    }

    std::string_view ConsoleLogger::GetLevelName(LogLevel level) const {
        switch (level) {
        case LogLevel::Trace:   return "TRACE";
        case LogLevel::Debug:   return "DEBUG";
        case LogLevel::Info:    return "INFO ";
        case LogLevel::Warning: return "WARN ";
        case LogLevel::Error:   return "ERROR";
        case LogLevel::Fatal:   return "FATAL";
        default:                return "UNKNW";
        }
    }

    void ConsoleLogger::SetColor(LogLevel level) {
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD colorAttributes = FOREGROUND_INTENSITY;

        switch (level) {
        case LogLevel::Trace:
            colorAttributes = FOREGROUND_INTENSITY;
            break;
        case LogLevel::Debug:
            colorAttributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            break;
        case LogLevel::Info:
            colorAttributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            break;
        case LogLevel::Warning:
            colorAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            break;
        case LogLevel::Error:
            colorAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
            break;
        case LogLevel::Fatal:
            colorAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY;
            break;
        }
        SetConsoleTextAttribute(hConsole, colorAttributes);
#endif
    }

    void ConsoleLogger::ResetColor() {
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 7);
#endif
    }

}