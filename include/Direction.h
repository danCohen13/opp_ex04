#pragma once

#include <type_traits>

constexpr int NUM_DIRECTIONS = 6;
constexpr int MIN_DIRECTION_VAL = 0;
constexpr int MAX_DIRECTION_VAL = 5;
constexpr float DIRECTION_ANGLE_STEP = 60.0f;

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
        return static_cast<Direction>((static_cast<int>(direction) + 3) % NUM_DIRECTIONS);
    }

    static Direction rotateClockwise(Direction direction) {
        return static_cast<Direction>((static_cast<int>(direction) + 1) % NUM_DIRECTIONS);
    }

    static Direction rotateCounterClockwise(Direction direction) {
        return static_cast<Direction>((static_cast<int>(direction) + 5) % NUM_DIRECTIONS);
    }

    static float toAngle(Direction dir)
    {
        switch (dir)
        {
        case Direction::NorthEast: return -DIRECTION_ANGLE_STEP;
        case Direction::East:      return   0.0f;
        case Direction::SouthEast: return  DIRECTION_ANGLE_STEP;
        case Direction::SouthWest: return 2.0f * DIRECTION_ANGLE_STEP;
        case Direction::West:      return 3.0f * DIRECTION_ANGLE_STEP;
        case Direction::NorthWest: return -2.0f * DIRECTION_ANGLE_STEP;
        }
        return 0.f;
    }
};