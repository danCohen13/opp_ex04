#pragma once

#include "Direction.h"
#include <vector>

class Bulb {
public:
    Bulb(const std::vector<Direction>& initialArms, bool isCentral = false);
    ~Bulb() = default;

    void rotateClockwise();
    void rotateCounterClockwise();
    void setLitState(bool isLit);

    bool isLit() const;
    bool isCentral() const;
    int getOrientation() const;

    bool hasArm(Direction direction) const;

private:
    int m_orientation;
    bool m_isLit;
    const bool m_isCentral;
    std::vector<bool> m_initialArms;

};