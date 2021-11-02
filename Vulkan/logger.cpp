#include "logger.h"
#include <iostream>
#include <Windows.h>

namespace logger
{
    enum class log_level : uint8_t
    {
        info,
        warning,
        error,
        critical
    };

    void log(const std::string& message, const log_level level)
    {
        switch (level)
        {
        case log_level::info:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);
            break;

        case log_level::warning:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            break;

        case log_level::error:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            break;

        case log_level::critical:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 206);
            break;
        }

        std::cout << message << "\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);
    }

    void info(const std::string& message)
    {
        log(message, log_level::info);
    }

    void warning(const std::string& message)
    {
        log(message, log_level::warning);
    }

    void error(const std::string& message)
    {
        log(message, log_level::error);
    }

    void critical(const std::string& message)
    {
        log(message, log_level::critical);
    }
}