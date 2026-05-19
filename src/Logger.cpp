#include "Logger.hpp"
#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>

void Logger::logError(const std::string& errorMessage) {
    // Ouverture en mode ajout (append)
    std::ofstream logFile("log.txt", std::ios_base::app);

    if (logFile.is_open()) {
        // Horodatage de l'erreur
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        logFile << "[" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S") << "] "
            << errorMessage << "\n";

        logFile.close();
    }
    else {
        // Repli de secours sur la sortie d'erreur standard si le disque est verrouillé
        std::cerr << "Impossible d'écrire dans log.txt ! Erreur d'origine : " << errorMessage << std::endl;
    }
}