#pragma once

#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>

class Utility
{
public:
    static std::string GetCurrentDateTime()
    {
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        auto local_time = *std::localtime(&time_t_now);

        std::ostringstream oss;
        oss << std::put_time(&local_time, "[%d/%m/%Y-%H:%M:%S]");
        return oss.str();
    }

    static std::string ToUpper(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }

    static std::string& ClearNewLine(std::string& str)
    {
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
        return str;
    }
};