#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "state/State.h"
#include "DeltaTimeClock.h"

// SMFML Include
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

// Standard Library Include
#include <random>
#include <cmath>

/*
* @class PlayingState
* @brief Playing State of the Game - Signifies the User is playing the Game
* 
* Playing State will give user access to Paused State
*/
class PlayingState : public State
{
public:
	PlayingState(StateManager* manager);
	~PlayingState() = default;

	virtual void handleInput() override;
	virtual void update() override;
	virtual void render() override;
private:
	// Private Functions
	void initialisePaddles();								// Sets up the Left and Right Paddles
	void initialiseBall();									// Sets up the Ball
	void initialiseSounds();								// Loads Sounds from Files

	void moveAI();
	void checkScored();
	void checkPaddleCollisions();
	void checkWallCollisions();

	sf::RenderWindow& window;
	float width;
	float height;

	float deltaTime = 0.f;
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

	// Score Values
	int leftScore = 0;
	int rightScore = 0;
};

#endif // PLAYINGSTATE_H