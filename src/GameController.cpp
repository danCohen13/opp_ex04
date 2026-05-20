#include "GameController.h"
#include "LightPropagationSystem.h"
#include "HexGeometry.h"

GameController::GameController(Board& board, RenderSystem& renderSystem,
    BoardRenderer& boardRenderer, ResourceManager& resourceManager)
    : m_board(board),
    m_renderSystem(renderSystem),
    m_boardRenderer(boardRenderer),
    m_resourceManager(resourceManager),
    m_currentState(GameState::Playing),
    m_successDuration(4.f) {
    LightPropagationSystem::updatePropagation(m_board);
}

void GameController::handleInput() {
    sf::RenderWindow& window = m_renderSystem.getWindow();

    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_currentState = GameState::Exiting;
            window.close();
        }
        if (m_currentState == GameState::Playing) {
            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (const auto& pair : m_board.getAllBulbs()) {
                    HexPosition pos = pair.first;
                    if (m_boardRenderer.isTileClicked(pos, mousePos)) {
                        if (mouse->button == sf::Mouse::Button::Left)
                            m_board.getBulb(pos).rotateClockwise();
                        else if (mouse->button == sf::Mouse::Button::Right)
                            m_board.getBulb(pos).rotateCounterClockwise();
                        LightPropagationSystem::updatePropagation(m_board);
                        break;
                    }
                }
            }
        }
    }
}

void GameController::update() {
    if (m_currentState == GameState::SuccessAnimation) {
        float elapsed = m_successClock.getElapsedTime().asSeconds();
        float progress = elapsed / m_successDuration;

        if (progress > 1.f) progress = 1.f;

        m_renderSystem.renderSuccess(m_boardRenderer, progress);

        if (elapsed >= m_successDuration) {
            m_currentState = GameState::LevelTransition;
        }
        return;
    }

    if (m_currentState != GameState::Playing) return;

    bool allLit = true;
    for (const auto& pair : m_board.getAllBulbs()) {
        if (!pair.second.isLit()) { allLit = false; break; }
    }

    if (allLit) {
        m_currentState = GameState::SuccessAnimation;
        m_successClock.restart();
    }
}

GameState GameController::getCurrentState() const {
    return m_currentState;
}