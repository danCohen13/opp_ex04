#pragma once

// Simple structure representing a coordinate point in a hexagonal axial system
struct HexPosition {
    int q; // Column axis
    int r; // Diagonal row axis

    // Strict weak ordering operator needed to use HexPosition as a key in STL containers like std::map
    bool operator<(const HexPosition& other) const {
        if (q != other.q) {
            return q < other.q;
        }
        return r < other.r;
    }

    // Equality operator for simple direct comparison
    bool operator==(const HexPosition& other) const {
        return (q == other.q && r == other.r);
    }
};