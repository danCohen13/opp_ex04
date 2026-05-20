#pragma once

struct HexPosition {
    int q; 
    int r; 

    bool operator<(const HexPosition& other) const {
        if (q != other.q) {
            return q < other.q;
        }
        return r < other.r;
    }

    bool operator==(const HexPosition& other) const {
        return (q == other.q && r == other.r);
    }
};