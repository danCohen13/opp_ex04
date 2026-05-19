#pragma once

#include <SFML/Graphics.hpp>
#include "BoardRenderer.h"

// Master graphics subsystem managing the application window lifecycle and framing
class RenderSystem {
public:
    RenderSystem();
    ~RenderSystem() = default;

    // Disallow duplication of the hardware window context
    RenderSystem(const RenderSystem&) = delete;
    RenderSystem& operator=(const RenderSystem&) = delete;

    // Returns a mutable reference to the underlying operating system window
    sf::RenderWindow& getWindow();

    // Clears the buffer, executes underlying drawing delegates, and flips the screen display
    void render(BoardRenderer& boardRenderer);

private:
    sf::RenderWindow m_window;
};