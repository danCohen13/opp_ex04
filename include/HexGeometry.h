#pragma once

#include "HexPosition.h"
#include <vector>

class HexGeometry {
public:
    HexGeometry() = delete;
    ~HexGeometry() = delete;

    // Returns the 6 adjacent axial coordinates for any given cell position
    static std::vector<HexPosition> getNeighbors(const HexPosition& position);

private:
    static const std::vector<HexPosition> m_neighborOffsets;
};