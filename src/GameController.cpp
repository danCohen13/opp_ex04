#include "GameController.h"
#include "LightPropagationSystem.h"
#include "HexGeometry.h"

GameController::GameController(Board& board, RenderSystem& renderSystem, BoardRenderer& boardRenderer, ResourceManager& resourceManager)
    : m_board(board),
    m_renderSystem(renderSystem),
    m_boardRenderer(boardRenderer),
    m_resourceManager(resourceManager),
    m_currentState(GameState::Playing) {
    LightPropagationSystem::updatePropagation(m_board);
}

void GameController::handleInput() {
    sf::RenderWindow& window = m_renderSystem.getWindow();

    // CORRECTION SFML 3 : La boucle d'événements retourne des objets typés via std::optional
    while (const std::optional<sf::Event> event = window.pollEvent()) {

        // Vérification de fermeture de la fenêtre
        if (event->is<sf::Event::Closed>()) {
            m_currentState = GameState::Exiting;
            window.close();
        }

        if (m_currentState == GameState::Playing) {
            // Extraction sécurisée des événements de clic de souris
            if (const auto* mouseButtonEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                for (const auto& pair : m_board.getAllBulbs()) {
                    HexPosition pos = pair.first;

                    if (m_boardRenderer.isTileClicked(pos, mousePos)) {
                        // Tri selon le bouton cliqué (Enum de SFML 3)
                        if (mouseButtonEvent->button == sf::Mouse::Button::Left) {
                            m_board.getBulb(pos).rotateClockwise();
                        }
                        else if (mouseButtonEvent->button == sf::Mouse::Button::Right) {
                            m_board.getBulb(pos).rotateCounterClockwise();
                        }

                        LightPropagationSystem::updatePropagation(m_board);
                        break;
                    }
                }
            }
        }
    }
}

void GameController::update() {
    if (m_currentState != GameState::Playing) {
        return;
    }

    bool allLit = true;
    for (const auto& pair : m_board.getAllBulbs()) {
        if (!pair.second.isLit()) {
            allLit = false;
            break;
        }
    }

    if (allLit) {
        m_currentState = GameState::Victory;
    }
}

GameState GameController::getCurrentState() const {
    return m_currentState;
}