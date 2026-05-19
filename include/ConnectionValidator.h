#pragma once

#include "HexPosition.h"
#include "Direction.h"
#include "Board.h"

class ConnectionValidator {
public:
    ConnectionValidator() = delete;
    ~ConnectionValidator() = delete;

    static bool canConnect(const Board& board, const HexPosition& from, const HexPosition& to, Direction dir);
};