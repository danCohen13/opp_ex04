#include "Bulb.h"

Bulb::Bulb(const std::vector<Direction>& initialArms, bool isCentral)
    : m_orientation(0),
    m_isLit(isCentral),
    m_isCentral(isCentral),
    m_initialArms(6, false) {

    for (const auto& direction : initialArms) {
        m_initialArms[static_cast<int>(direction)] = true;
    }
}

void Bulb::rotateClockwise() {
    m_orientation = (m_orientation + 1) % 6;
}

void Bulb::rotateCounterClockwise() {
    m_orientation = (m_orientation + 5) % 6;
}

void Bulb::setLitState(bool isLit) {
    if (m_isCentral) {
        m_isLit = true; 
    }
    else {
        m_isLit = isLit;
    }
}

bool Bulb::isLit() const {
    return m_isLit;
}

bool Bulb::isCentral() const {
    return m_isCentral;
}

int Bulb::getOrientation() const {
    return m_orientation;
}

bool Bulb::hasArm(Direction direction) const {
    int dirValue = static_cast<int>(direction);

    int originalIndex = (dirValue - m_orientation + 6) % 6;

    return m_initialArms[originalIndex];
}