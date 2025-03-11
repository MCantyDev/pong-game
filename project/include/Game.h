#ifndef GAME_H
#define GAME_H

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
	~Game();

	void run();

private:
	// Member Functions
	// Initialisation
	void initialisePaddles();								// Sets up the Left and Right Paddles
	void initialiseBall();									// Sets up the Ball
	void initialiseSounds();								// Loads Sounds from Files

	// Member Variables
	// Window Size
	const char* title = "Pong";
	const float WIDTH = 1200.f;
	const float HEIGHT = 800.f;
	sf::RenderWindow window;

	// State
	bool isPlaying = false;

	// SFML Clocks
	sf::Clock clock;										// For DeltaTime calculations
	sf::Clock delayClock;									// For Move Delay of Ball from Game Start and Scoring

	// Computer Values
	sf::Clock computerClock;								// For Computer (AI) movement delay -> Turns out it is possible to win but EXTREMELY DIFFICULT
	float computerPaddleSpeed = 0.f;						// Speed Computer Paddle moves in the Y-Axis
	sf::Time computerTime = sf::milliseconds(1);			// Delay between Computer changing move direction

	// Paddle Values
	sf::RectangleShape leftPaddle;
	sf::RectangleShape rightPaddle;
	const sf::Vector2f paddleSize = sf::Vector2f(40, 120);	// Paddle Size
	const float paddleSpeed = 500.f;						// Speed Paddle moves in the Y-Axis
	
	// Ball Values
	sf::CircleShape ball;
	const float ballRadius = 15.f;							// Raidus of the Ball
	const float ballSpeed = 600.f;							// Speed of Ball (Faster than Paddle)
	sf::Angle ballAngle = sf::degrees(-180);				// Ball goes towards Player
	bool moveBall = false;									// Make it so we can define when the Ball should BEGIN moving

	// Random Number Generator
	std::random_device rando;
	std::mt19937 rng;

	// Sound Buffers
	sf::SoundBuffer paddleBounceBuffer;
	sf::SoundBuffer wallBounceBuffer;
	sf::SoundBuffer scorePointBuffer;

	// Sounds
	sf::Sound paddleBounce = sf::Sound(paddleBounceBuffer);
	sf::Sound wallBounce = sf::Sound(wallBounceBuffer);
	sf::Sound scorePoint = sf::Sound(scorePointBuffer);

	// Music
	sf::Music backgroundMusic;

	// Score Values
	int leftScore = 0;
	int rightScore = 0;
};

#endif // GAME_H