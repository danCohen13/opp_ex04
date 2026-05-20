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
#include <memory>

class Game {
public:
    Game();
    ~Game() = default;
    void run();

private:
    void initializePlaylist();
    void loadNextLevel();
    void resetController();

    Board                          m_board;
    ResourceManager                m_resourceManager;
    BoardRenderer                  m_boardRenderer;
    RenderSystem                   m_renderSystem;
    std::vector<std::string>       m_levelPlaylist;
    size_t                         m_currentLevelIndex;
    std::unique_ptr<GameController> m_controller;
};