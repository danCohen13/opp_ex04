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

    void handleInput();
    void update();
    GameState getCurrentState() const;

private:
    Board& m_board;
    RenderSystem& m_renderSystem;
    BoardRenderer& m_boardRenderer;
    ResourceManager& m_resourceManager;
    GameState m_currentState;

    sf::Clock        m_successClock;      
    float            m_successDuration;
};