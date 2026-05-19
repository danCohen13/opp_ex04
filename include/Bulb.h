#pragma once

#include "Direction.h"
#include <vector>

class Bulb {
public:
    // Initializes a bulb with its original structural layout
    Bulb(const std::vector<Direction>& initialArms, bool isCentral = false);
    ~Bulb() = default;

    // State Modifiers
    void rotateClockwise();
    void rotateCounterClockwise();
    void setLitState(bool isLit);

    // Getters for game logic and rendering systems
    bool isLit() const;
    bool isCentral() const;
    int getOrientation() const;

    // Checks if the bulb has an active physical arm pointing in a specific direction
    bool hasArm(Direction direction) const;

private:
    int m_orientation;               // Value between 0 and 5 (steps of 60 degrees)
    bool m_isLit;                    // Current propagation status
    const bool m_isCentral;          // Central power source flag, always lit
    std::vector<bool> m_initialArms; // Fixed-size internal mask of 6 elements
};