#pragma once

#include <string>

class FileUtils {
public:
    // Désactivation des constructeurs pour imposer une classe utilitaire statique pure
    FileUtils() = delete;
    ~FileUtils() = delete;

    // Vérifie si un fichier existe et peut être ouvert en lecture
    static bool fileExists(const std::string& filepath);

    // Vérifie si le fichier possède la bonne extension (ex: ".txt")
    static bool hasExtension(const std::string& filepath, const std::string& extension);
};