#pragma once

// Strongly typed enum representing the 6 physical directions of a regular hexagon in clockwise order
enum class Direction {
    N = 0, // North
    NE = 1, // North-East
    SE = 2, // South-East
    S = 3, // South
    SW = 4, // South-West
    NW = 5  // North-West
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
};