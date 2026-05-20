#pragma once

#include <string>

class Logger {
public:
    Logger() = delete;

    static void logError(const std::string& errorMessage);
};