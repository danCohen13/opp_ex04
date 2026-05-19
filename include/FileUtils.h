#pragma once

#include <string>
#include "Direction.h" // CORRECTION : Élimine l'erreur syntax error: identifier 'Direction'

class FileUtils {
public:
    FileUtils() = delete;
    ~FileUtils() = delete;

    static bool fileExists(const std::string& filepath);
    static bool hasExtension(const std::string& filepath, const std::string& extension);
    static const std::string& directionToString(Direction dir);
};