#pragma once

#include "GameState.h"
#include "Board.h"
#include "Level.h"
#include "ResourceManager.h"
#include "BoardRenderer.h"
#include "RenderSystem.h"
#include "GameController.h"
#include <vector>
#include <string>

class Game {
public:
    Game();
    ~Game() = default;

    // Main structural engine loop entry point
    void run();

private:
    // Initializes containers and registers level file sequences
    void initializePlaylist();

    // Clears the current map and hydrater-builds the next level from playlist configuration
    void loadNextLevel();

    Board m_board;
    ResourceManager m_resourceManager;
    BoardRenderer m_boardRenderer;
    RenderSystem m_renderSystem;

    std::vector<std::string> m_levelPlaylist;
    size_t m_currentLevelIndex;
};