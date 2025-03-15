#ifndef GAME_H
#define GAME_H

// Management Systems
#include "StateManager.h"
#include "DeltaTimeClock.h"
#include "RenderWindowManager.h"
#include "SoundManager.h"

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
	StateManager stateManager;
	
	// DeltaTime
	DeltaTimeClock* deltaClock = nullptr;

	// Sounds
	SoundManager* soundManager = nullptr;
};

#endif // GAME_H