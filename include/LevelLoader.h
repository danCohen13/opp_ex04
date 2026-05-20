#pragma once

#include "Level.h"
#include <string>

class LevelLoader {
public:
    LevelLoader() = delete;
    ~LevelLoader() = delete;

    static Level loadFromFile(const std::string& filepath);
};