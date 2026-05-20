#pragma once

#include "HexPosition.h"
#include <vector>

class HexGeometry {
public:
    HexGeometry() = delete;
    ~HexGeometry() = delete;

    static std::vector<HexPosition> getNeighbors(const HexPosition& position);

private:
    static const std::vector<HexPosition> m_neighborOffsets;
};