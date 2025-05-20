#ifndef GAME_H
#define GAME_H

// Management Systems
#include "command/InputManager.h"
#include "core/StateManager.h"
#include "core/DeltaTimeClock.h"
#include "core/RenderWindowManager.h"
#include "core/SoundManager.h"
#include "core/ScoreManager.h"

// SMFL Includes
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

// Standard Library Includes
#include <iostream>
#include <cmath>
#include <random>

/**
 * @class Game
 * @brief Entry point to the Pong game.
 * 
 * The Game class acts as the core controller for the application.
 * It is responsible for initializing all core systems required for gameplay,
 * including state management, input handling, rendering, and the main game loop.
 */
class Game
{
public:
    Game();
    ~Game() = default;

    /**
     * @brief Starts the main game loop.
     * 
     * Continuously updates and renders the current game state.
     * Handles timing and transitions between different states.
     */
    void run();

private:
	// Member Functions
	// Initialisation
	void initialiseSounds(); // Loads Sounds from Files
	void initialiseBackgroundMusic(); // Loads Sounds from Files

	// Member Variables

	// Window
	const char* title = "Pong";
	const float WIDTH = 1200.f;
	const float HEIGHT = 800.f;
	sf::RenderWindow* window;

	// States
	StateManager* stateManager = nullptr;

	// Input Manager
	InputManager* inputManager = nullptr;
	
	// DeltaTime
	DeltaTimeClock* deltaClock = nullptr;

	// Sounds
	SoundManager* soundManager = nullptr;

	// Score Manager
	ScoreManager* scoreManager = nullptr;
};

#endif // GAME_H