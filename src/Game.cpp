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
    // CORRECTION : Utilisation de chemins relatifs remontant à la racine du projet
    // afin que Ninja trouve les fichiers depuis le dossier out/build/x64-Debug/
    m_levelPlaylist.push_back("../../../level1.txt");
    m_levelPlaylist.push_back("../../../level2.txt");
    m_levelPlaylist.push_back("../../../level3.txt");
}

void Game::loadNextLevel() {
    if (m_currentLevelIndex >= m_levelPlaylist.size()) {
        return;
    }

    // Clear previous simulation variables and topography maps safely
    m_board.clear();

    // Factory invocation to load un-hydrated configuration from file
    std::string currentFile = m_levelPlaylist[m_currentLevelIndex];
    Level loadedLevel = LevelLoader::loadFromFile(currentFile);

    // Build the dynamic runtime simulation nodes from static immutable blueprints
    for (const auto& info : loadedLevel.getBulbConfigurations()) {
        Bulb newBulb(info.initialArms, info.isCentral);
        m_board.addBulb(info.position, newBulb);
    }

    // Calculate topological graph adjacencies dynamically based on coordinates
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

void Game::run() {
    // Hydrate the layout with the initial structural puzzle configuration
    loadNextLevel();

    // Stack allocation of the input coordinator instance
    GameController controller(m_board, m_renderSystem, m_boardRenderer, m_resourceManager);
    sf::RenderWindow& window = m_renderSystem.getWindow();

    // Unified application pipeline execution loop
    while (window.isOpen() && controller.getCurrentState() != GameState::Exiting) {

        // 1. Frame Input Phase
        controller.handleInput();

        // 2. Frame Logic Upgrades Phase
        controller.update();

        // 3. State Engine Check and Scene Swapping Layout
        if (controller.getCurrentState() == GameState::LevelTransition) {
            m_currentLevelIndex++;
            if (m_currentLevelIndex < m_levelPlaylist.size()) {
                loadNextLevel();
                // Local state reset handled by controller context recreation or manual invoke
            }
            else {
                break; // Final game victory state reached, exit loop smoothly
            }
        }

        // 4. Graphics Render Processing Phase
        m_renderSystem.render(m_boardRenderer);
    }
}