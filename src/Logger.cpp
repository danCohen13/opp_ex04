#include "Logger.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

void Logger::logError(const std::string& errorMessage) {
    std::ofstream logFile("log.txt", std::ios_base::app);

    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        std::time_t in_time_t = std::chrono::system_clock::to_time_t(now);

        // Safe Microsoft secure alternative to prevent C4996 error
        std::tm timeInfo;
        localtime_s(&timeInfo, &in_time_t);

        logFile << "[" << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << "] "
            << errorMessage << "\n";

        logFile.close();
    }
    else {
        std::cerr << "Impossible to write to log.txt! Original error: " << errorMessage << std::endl;
    }
}