#pragma once

#include <type_traits>

enum class Direction {
    NorthEast = 0, 
    East,
    SouthEast,
    SouthWest,
    West,
    NorthWest
};

class DirectionUtils {
private:
    DirectionUtils() = default;

public:
    static Direction getOpposite(Direction direction) {
        return static_cast<Direction>((static_cast<int>(direction) + 3) % 6);
    }

    static Direction rotateClockwise(Direction direction) {
        return static_cast<Direction>((static_cast<int>(direction) + 1) % 6);
    }

    static Direction rotateCounterClockwise(Direction direction) {
        return static_cast<Direction>((static_cast<int>(direction) + 5) % 6);
    }

    static float toAngle(Direction dir)
    {
        switch (dir)
        {
        case Direction::NorthEast: return -60.0f;
        case Direction::East:      return   0.0f;
        case Direction::SouthEast: return  60.0f;
        case Direction::SouthWest: return 120.0f;
        case Direction::West:      return 180.0f;
        case Direction::NorthWest: return -120.0f;
        }
        return 0.f;
    }
};