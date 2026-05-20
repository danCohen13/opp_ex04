#pragma once

#include "HexPosition.h"
#include "Direction.h"
#include <vector>

struct BulbInfo {
    HexPosition position;
    std::vector<Direction> initialArms;
    bool isCentral;
};

class Level {
public:
    Level() = default;
    ~Level() = default;

    void addBulbInfo(const BulbInfo& info);
    void setGridSize(int size);

    int getGridSize() const;
    const std::vector<BulbInfo>& getBulbConfigurations() const;

    bool isValid() const;

private:
    int m_gridSize = 0;
    std::vector<BulbInfo> m_bulbPresets;
};