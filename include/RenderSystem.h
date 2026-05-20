#pragma once

#include <SFML/Graphics.hpp>
#include "BoardRenderer.h"

class RenderSystem {
public:
    RenderSystem();
    ~RenderSystem() = default;

    RenderSystem(const RenderSystem&) = delete;
    RenderSystem& operator=(const RenderSystem&) = delete;

    sf::RenderWindow& getWindow();

    void render(BoardRenderer& boardRenderer);

    void renderSuccess(BoardRenderer& boardRenderer, float progress);

private:
    sf::RenderWindow m_window;
    sf::Font         m_font;
};