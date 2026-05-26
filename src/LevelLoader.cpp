#include "LevelLoader.h"
#include "FileUtils.h"
#include "Exceptions.h"
#include "Direction.h"
#include <fstream>
#include <sstream>

Level LevelLoader::loadFromFile(const std::string& filepath) {
    if (!FileUtils::fileExists(filepath)) {
        throw FileNotFoundException(filepath);
    }

    Level level;
    std::ifstream file(filepath);
    std::string line;

    if (!std::getline(file, line)) {
        throw CorruptedLevelException("Empty level file: " + filepath);
    }

    std::istringstream sizeStream(line);
    int gridSize = 0;
    if (!(sizeStream >> gridSize) || gridSize <= 0) {
        throw CorruptedLevelException("Invalid grid size definition.");
    }
    level.setGridSize(gridSize);

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream bulbStream(line);
        int q = 0, r = 0;
        int isCentralRaw = 0;
        int numArms = 0;

        if (!(bulbStream >> q >> r >> isCentralRaw >> numArms)) {
            throw CorruptedLevelException("Malformed bulb coordinate or state token.");
        }

        BulbInfo info;
        info.position = { q, r };
        info.isCentral = (isCentralRaw != 0);
        info.initialArms.reserve(numArms);

        for (int i = 0; i < numArms; ++i) {
            int dirValue = 0;
            if (!(bulbStream >> dirValue) || dirValue < MIN_DIRECTION_VAL || dirValue > MAX_DIRECTION_VAL) {
                throw CorruptedLevelException("Invalid arm direction index value.");
            }
            info.initialArms.push_back(static_cast<Direction>(dirValue));
        }

        level.addBulbInfo(info);
    }

    if (!level.isValid()) {
        throw CorruptedLevelException("Level validation failed. Missing critical components.");
    }

    return level;
}