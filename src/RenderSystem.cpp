#include "RenderSystem.h"

RenderSystem::RenderSystem()
// CORRECTION SFML 3 : Passage par sf::Vector2u pour le mode vidéo
    : m_window(sf::VideoMode(sf::Vector2u(800, 600)), "Lights Puzzle Game", sf::Style::Close) {
    m_window.setFramerateLimit(60);
}

sf::RenderWindow& RenderSystem::getWindow() {
    return m_window;
}

void RenderSystem::render(BoardRenderer& boardRenderer) {
    m_window.clear(sf::Color::Black);
    boardRenderer.render(m_window);
    m_window.display();
}