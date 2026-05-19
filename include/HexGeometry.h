#pragma once

#include "HexPosition.h"
#include <vector>
#include <array>

// Mathematical utility class for hexagonal map calculations and neighbor discovery
class HexGeometry {
public:
    HexGeometry() = delete;
    ~HexGeometry() = delete;

    // Generates the 6 immediate neighbors of a given axial position to dynamically build the graph nodes
    static std::vector<HexPosition> getNeighbors(const HexPosition& position) {
        // Clockwise axial direction vectors starting from North (matching Direction enum values)
        static const std::array<HexPosition, 6> directionVectors = { {
            { 0, -1}, // N
            { 1, -1}, // NE
            { 1,  0}, // SE
            { 0,  1}, // S
            {-1,  1}, // SW
            {-1,  0}  // NW
        } };

        std::vector<HexPosition> neighbors;
        neighbors.reserve(6);

        for (const auto& vec : directionVectors) {
            neighbors.push_back({ position.q + vec.q, position.r + vec.r });
        }

        return neighbors;
    }
};