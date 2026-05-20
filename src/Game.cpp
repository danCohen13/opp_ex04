#include "Game.h"
#include "HexGeometry.h"
#include "LevelLoader.h"
#include <iostream>

Game::Game()
    : m_boardRenderer(m_board, m_resourceManager),
    m_currentLevelIndex(0) {
    initializePlaylist();
}

void Game::initializePlaylist() {
    m_levelPlaylist.push_back("../../../level1.txt");
    m_levelPlaylist.push_back("../../../level2.txt");
    m_levelPlaylist.push_back("../../../level3.txt");
}

void Game::loadNextLevel() {
    if (m_currentLevelIndex >= m_levelPlaylist.size()) return;

    m_board.clear();

    std::string currentFile = m_levelPlaylist[m_currentLevelIndex];
    Level loadedLevel = LevelLoader::loadFromFile(currentFile);

    for (const auto& info : loadedLevel.getBulbConfigurations()) {
        Bulb newBulb(info.initialArms, info.isCentral);
        m_board.addBulb(info.position, newBulb);
    }

    for (const auto& pair : m_board.getAllBulbs()) {
        HexPosition currentPos = pair.first;
        std::vector<HexPosition> potentialNeighbors = HexGeometry::getNeighbors(currentPos);
        for (const auto& neighborPos : potentialNeighbors) {
            if (m_board.getAllBulbs().find(neighborPos) != m_board.getAllBulbs().end()) {
                m_board.addConnection(currentPos, neighborPos);
            }
        }
    }
}

void Game::resetController() {
    m_controller = std::make_unique<GameController>(
        m_board, m_renderSystem, m_boardRenderer, m_resourceManager
    );
}

void Game::run() {
    loadNextLevel();
    resetController();

    sf::RenderWindow& window = m_renderSystem.getWindow();

    while (window.isOpen() && m_controller->getCurrentState() != GameState::Exiting) {
        m_controller->handleInput();
        m_controller->update();

        if (m_controller->getCurrentState() == GameState::LevelTransition) {
            m_currentLevelIndex++;
            if (m_currentLevelIndex < m_levelPlaylist.size()) {
                loadNextLevel();
                resetController();
            }
            else {
                window.close();
            }
        }

        if (m_controller->getCurrentState() == GameState::Playing) {
            m_renderSystem.render(m_boardRenderer);
        }
    }
}