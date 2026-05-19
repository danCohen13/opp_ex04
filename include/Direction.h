#pragma once

// Strongly typed enum representing the 6 physical directions of a regular hexagon in clockwise order
enum class Direction {
    NorthEast = 0, // 30 degrees (formerly East)
    East,          // 90 degrees (formerly South-East)
    SouthEast,     // 150 degrees (formerly South-West)
    SouthWest,     // 210 degrees (formerly West)
    West,          // 270 degrees (formerly North-West)
    NorthWest      // 330 degrees (formerly North-East)
};

// Utility class containing stateless static methods to manipulate Directions
class DirectionUtils {
public:
    DirectionUtils() = delete;
    ~DirectionUtils() = delete;

    // Returns the opposite direction, crucial for validating physical wire connections between adjacent bulbs
    static Direction getOpposite(Direction direction) {
        // Adding 3 shifts by 180 degrees in our 6-axis coordinate system
        return static_cast<Direction>((static_cast<int>(direction) + 3) % 6);
    }

    // Returns the direction rotated 60 degrees clockwise
    static Direction rotateClockwise(Direction direction) {
        return static_cast<Direction>((static_cast<int>(direction) + 1) % 6);
    }

    // Returns the direction rotated 60 degrees counter-clockwise
    static Direction rotateCounterClockwise(Direction direction) {
        return static_cast<Direction>((static_cast<int>(direction) + 5) % 6);
    }

    static float toAngle(Direction dir)
    {
        switch (dir)
        {
        case Direction::NorthEast:
            return -30.f;

        case Direction::East:
            return 30.f;

        case Direction::SouthEast:
            return 90.f;

        case Direction::SouthWest:
            return 150.f;

        case Direction::West:
            return 210.f;

        case Direction::NorthWest:
            return 270.f;
        }

        return 0.f;
    }

};