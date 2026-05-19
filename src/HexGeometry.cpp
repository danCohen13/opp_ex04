#include "HexGeometry.h"

// Static definition tracking the 6 physical directions in 60-degree increments
const std::vector<HexPosition> HexGeometry::m_neighborOffsets = {
    { 1, -1 }, // North-East (Index 0 -> 30°)
    { 1, 0 },  // East       (Index 1 -> 90°)
    { 0, 1 },  // South-East (Index 2 -> 150°)
    { -1, 1 }, // South-West (Index 3 -> 210°)
    { -1, 0 }, // West       (Index 4 -> 270°)
    { 0, -1 }  // North-West (Index 5 -> 330°)
};

std::vector<HexPosition> HexGeometry::getNeighbors(const HexPosition& position) {
    std::vector<HexPosition> neighbors;
    neighbors.reserve(6);

    for (const auto& offset : m_neighborOffsets) {
        neighbors.push_back({ position.q + offset.q, position.r + offset.r });
    }

    return neighbors;
}