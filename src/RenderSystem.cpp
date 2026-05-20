#include "RenderSystem.h"
#include <cmath>

RenderSystem::RenderSystem()
    : m_window(sf::VideoMode(sf::Vector2u(800, 600)), "Lights Puzzle Game", sf::Style::Close) {
    m_window.setFramerateLimit(60);
    if (!m_font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        m_font.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    }
}

sf::RenderWindow& RenderSystem::getWindow() {
    return m_window;
}

void RenderSystem::render(BoardRenderer& boardRenderer) {
    m_window.clear(sf::Color::Black);
    boardRenderer.render(m_window);
    m_window.display();
}

void RenderSystem::renderSuccess(BoardRenderer& boardRenderer, float progress) {

    m_window.clear(sf::Color::Black);
    boardRenderer.render(m_window);

    float alpha = 0.f;
    if (progress < 0.15f)
        alpha = progress / 0.15f;           
    else if (progress > 0.85f)
        alpha = 1.f - (progress - 0.85f) / 0.15f; 
    else
        alpha = 1.f;

    sf::RectangleShape overlay(sf::Vector2f(800.f, 600.f));
    overlay.setFillColor(sf::Color(0, 0, 0, static_cast<std::uint8_t>(alpha * 160)));
    m_window.draw(overlay);

    float cx = 400.f, cy = 300.f;
    int numStars = 12;
    for (int i = 0; i < numStars; ++i) {
        float angle = (static_cast<float>(i) / numStars) * 2.f * 3.14159f
            + progress * 6.28f * 0.5f; 
        float dist = 130.f + 20.f * std::sin(progress * 6.28f * 2.f + i);
        float x = cx + std::cos(angle) * dist;
        float y = cy + std::sin(angle) * dist;
        float size = 4.f + 3.f * std::sin(progress * 6.28f * 3.f + i * 0.8f);

        sf::CircleShape star(size);
        star.setOrigin(sf::Vector2f(size, size));
        star.setPosition(sf::Vector2f(x, y));

        std::uint8_t r = 255;
        std::uint8_t g = static_cast<std::uint8_t>(180 + 75 * std::sin(progress * 6.28f + i));
        std::uint8_t a = static_cast<std::uint8_t>(alpha * 220);
        star.setFillColor(sf::Color(r, g, 0, a));
        m_window.draw(star);
    }

    sf::Text text(m_font, "SUCCESS", 72);
    text.setStyle(sf::Text::Bold);

    float scale = 0.f;
    if (progress < 0.2f)
        scale = progress / 0.2f;
    else
        scale = 1.f;

    scale *= 1.f + 0.03f * std::sin(progress * 6.28f * 4.f);

    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f));
    text.setPosition(sf::Vector2f(cx, cy));
    text.setScale(sf::Vector2f(scale, scale));

    float glow = std::sin(progress * 6.28f * 3.f) * 0.5f + 0.5f;
    std::uint8_t rr = 255;
    std::uint8_t gg = static_cast<std::uint8_t>(200 + 55 * glow);
    std::uint8_t bb = static_cast<std::uint8_t>(50 * glow);
    text.setFillColor(sf::Color(rr, gg, bb, static_cast<std::uint8_t>(alpha * 255)));

    text.setOutlineThickness(3.f);
    text.setOutlineColor(sf::Color(180, 120, 0, static_cast<std::uint8_t>(alpha * 255)));

    m_window.draw(text);

    m_window.display();
}