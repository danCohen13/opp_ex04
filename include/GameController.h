#pragma once

#include "GameState.h"
#include "Board.h"
#include "RenderSystem.h"
#include "BoardRenderer.h"
#include "ResourceManager.h"

class GameController {
public:
    GameController(Board& board, RenderSystem& renderSystem, BoardRenderer& boardRenderer, ResourceManager& resourceManager);
    ~GameController() = default;

    // CORRECTION : Ces fonctions doivent obligatoirement être publiques pour être appelées par la classe Game
    void handleInput();
    void update();
    GameState getCurrentState() const;

private:
    Board& m_board;
    RenderSystem& m_renderSystem;
    BoardRenderer& m_boardRenderer;
    ResourceManager& m_resourceManager;
    GameState m_currentState;
};