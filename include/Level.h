#pragma once

#include "HexPosition.h"
#include "Direction.h"
#include <vector>

// Nested structure holding raw immutably loaded configuration for a single bulb cell
struct BulbInfo {
    HexPosition position;
    std::vector<Direction> initialArms;
    bool isCentral;
};

class Level {
public:
    Level() = default;
    ~Level() = default;

    // Modifiers used exclusively by the LevelLoader factory
    void addBulbInfo(const BulbInfo& info);
    void setGridSize(int size);

    // Read-only queries for the Game loop initialization
    int getGridSize() const;
    const std::vector<BulbInfo>& getBulbConfigurations() const;

    // Safety check to ensure data structural integrity before board building
    bool isValid() const;

private:
    int m_gridSize = 0;
    std::vector<BulbInfo> m_bulbPresets;
};