#pragma once

#include <SFML/Graphics.hpp>
#include "HexPosition.h"
#include "Board.h"
#include "ResourceManager.h"

class BoardRenderer {
public:
    BoardRenderer(const Board& board, ResourceManager& resourceManager);
    ~BoardRenderer() = default;

    void render(sf::RenderTarget& target);

    bool isTileClicked(const HexPosition& position, const sf::Vector2i& mousePos) const;

    sf::Vector2f hexToPixel(const HexPosition& position) const;

private:
    const Board& m_board;
    ResourceManager& m_resourceManager;
    const float m_hexRadius = 40.0f; 
};