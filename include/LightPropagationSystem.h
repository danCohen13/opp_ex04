#pragma once

#include "Board.h"

class LightPropagationSystem {
public:
    LightPropagationSystem() = delete;
    ~LightPropagationSystem() = delete;

    static void updatePropagation(Board& board);
};