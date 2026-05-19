#pragma once

#include <string>

class Logger {
public:
    // Désactivation des constructeurs pour en faire une classe utilitaire purement statique
    Logger() = delete;

    static void logError(const std::string& errorMessage);
};