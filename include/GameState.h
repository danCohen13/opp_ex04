#pragma once

// Represents the various logical phases of the game execution
enum class GameState {
    Menu,            // Initial screen or pause menu
    Playing,         // Core gameplay loop
    LevelTransition, // Handling screen between levels
    Victory,         // Final game success screen
    GameOver,        // Failure or termination
    Exiting          // Application teardown phase
};