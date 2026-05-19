#pragma once

#include <SFML/Graphics.hpp>
#include "HexPosition.h"
#include "Board.h"
#include "ResourceManager.h"

// Computes spatial positioning and boundaries for the hexagonal grid rendering
class BoardRenderer {
public:
    BoardRenderer(const Board& board, ResourceManager& resourceManager);
    ~BoardRenderer() = default;

    // Renders the entire collection of bulbs onto the target window
    void render(sf::RenderTarget& target);

    // Checks if a pixel screen position falls inside the geometric bounds of a specific hex tile
    bool isTileClicked(const HexPosition& position, const sf::Vector2i& mousePos) const;

    // Converts abstract axial coordinates into physical screen pixel offsets
    sf::Vector2f hexToPixel(const HexPosition& position) const;

private:
    const Board& m_board;
    ResourceManager& m_resourceManager;
    const float m_hexRadius = 40.0f; // Outer radius size of a single hexagon cell
};