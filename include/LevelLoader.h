#pragma once

#include "Level.h"
#include <string>

class LevelLoader {
public:
    LevelLoader() = delete;
    ~LevelLoader() = delete;

    // Parses a level configuration file and returns a validated Level object
    static Level loadFromFile(const std::string& filepath);
};