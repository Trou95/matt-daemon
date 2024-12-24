#pragma once

#include <iostream>
#include <fstream>

#include "../utility/utility.h"

enum E_LOG_LEVEL
{
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR
};

class Logger
{
public:
    Logger(const char *log_file) : LOG_FILE(log_file)
    {
        file.open(LOG_FILE, std::ios::app);
    }

    ~Logger()
    {
        file.close();
    }

    template <typename T>
    void logHelper(const T &arg)
    {
        file << arg;
    }

    template <typename T, typename... Args>
    void logHelper(const T &first, const Args &...rest)
    {
        file << first;
        logHelper(rest...);
    }

    template <typename... Args>
    void log(const Args &...args)
    {
        logHelper(args...);
        file << std::endl;
    }

    template <typename... Args>
    void LogInfo(const Args &...args)
    {
        file << Utility::GetCurrentDateTime() << " " << "[INFO] ";
        log(args...);
    }

    template <typename... Args>
    void LogWarning(const Args &...args)
    {
        file << Utility::GetCurrentDateTime() << " " << "[WARNING] ";
        log(args...);
    }

    template <typename... Args>
    void LogError(const Args &...args)
    {
        file << Utility::GetCurrentDateTime() << " " << "[ERROR] ";
        log(args...);
    }

private:
    const char *LOG_FILE;
    std::ofstream file;
};