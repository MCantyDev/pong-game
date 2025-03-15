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
* @brief Entry point to the Game
* 
* The Game class acts as the core of the game. It is responsible
* for initialising all systems required for gameplay, including game state
* management, input handling, and rendering
*/
class Game
{
public:
	Game();
	~Game() = default;

	void run();

private:
	// Member Functions
	// Initialisation
	void initialiseSounds();										// Loads Sounds from Files
	void initialiseBackgroundMusic();								// Loads Sounds from Files

	// Member Variables

	// Window
	const char* title = "Pong";
	const float WIDTH = 1200.f;
	const float HEIGHT = 800.f;
	sf::RenderWindow& window;

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