#include "ConnectionValidator.h"

bool ConnectionValidator::canConnect(const Board& board, const HexPosition& from, const HexPosition& to, Direction dir) {
    // Retrieve read-only references of both adjacent target bulbs
    const Bulb& sourceBulb = board.getBulb(from);
    const Bulb& targetBulb = board.getBulb(to);

    Direction oppositeDir = DirectionUtils::getOpposite(dir);

    // A valid connection requires mutual alignment of active conductive arms
    return sourceBulb.hasArm(dir) && targetBulb.hasArm(oppositeDir);
}