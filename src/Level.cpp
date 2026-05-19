#include "Level.h"

void Level::addBulbInfo(const BulbInfo& info) {
    m_bulbPresets.push_back(info);
}

void Level::setGridSize(int size) {
    m_gridSize = size;
}

int Level::getGridSize() const {
    return m_gridSize;
}

const std::vector<BulbInfo>& Level::getBulbConfigurations() const {
    return m_bulbPresets;
}

bool Level::isValid() const {
    // A level configuration requires a defined geometry and at least one power node
    if (m_gridSize <= 0 || m_bulbPresets.empty()) {
        return false;
    }

    bool hasCentralSource = false;
    for (const auto& info : m_bulbPresets) {
        if (info.isCentral) {
            hasCentralSource = true;
            break;
        }
    }

    return hasCentralSource;
}