#include "Bulb.h"

Bulb::Bulb(const std::vector<Direction>& initialArms, bool isCentral)
    : m_orientation(0),
    m_isLit(isCentral),
    m_isCentral(isCentral),
    m_initialArms(NUM_DIRECTIONS, false) {

    for (const auto& direction : initialArms) {
        m_initialArms[static_cast<int>(direction)] = true;
    }
}

void Bulb::rotateClockwise() {
    m_orientation = (m_orientation + 1) % NUM_DIRECTIONS;
}

void Bulb::rotateCounterClockwise() {
    m_orientation = (m_orientation + (NUM_DIRECTIONS - 1)) % NUM_DIRECTIONS;
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

    int originalIndex = (dirValue - m_orientation + NUM_DIRECTIONS) % NUM_DIRECTIONS;

    return m_initialArms[originalIndex];
}