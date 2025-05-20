#ifndef BALL_H
#define BALL_H

// Drawables
#include "drawables/Drawable.h"

// Singletons
#include "core/SoundManager.h"
#include "core/ScoreManager.h"

// Observable
#include "Observer/Observable.h"

// SFML Include
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

// Standard Library Include
#include <random>
#include <cmath>

class Paddle;

/**
 * @class Ball
 * @brief Represents the ball in the Pong game.
 *
 * Inherits from Drawable to enable rendering and positioning,
 * and Observable to notify observers (e.g., ScoreManager) of scoring events.
 *
 * Manages ball movement, collision detection with paddles and walls, and scoring.
 */
class Ball : public Drawable, public Observable<PaddleSide>
{
public:
	/**
	 * @brief Constructs a Ball with references to the two paddles for collision checks.
	 * @param p1 Pointer to Player One's paddle.
	 * @param p2 Pointer to Player Two's paddle.
	 */
	Ball(Paddle *p1, Paddle *p2);

	/**
	 * @brief Updates the ball's position and handles all collision logic.
	 */
	void update();

	// Pure Virtual Functions from Drawable
	virtual float getTop() const override;
	virtual float getBottom() const override;
	virtual float getLeft() const override;
	virtual float getRight() const override;

private:
	/**
	 * @brief Checks for and handles collision between the ball and the paddles.
	 */
	void paddleCollisionCheck();

	/**
	 * @brief Checks for and handles collision between the ball and the top/bottom walls.
	 */
	void wallCollisionCheck();

	/**
	 * @brief Checks if the ball has passed a paddle, updating the score accordingly.
	 */
	void scoreCollisionCheck();

	ScoreManager *scoreManager = nullptr;

	sf::CircleShape circle;
	float ballRadius = 15.f;
	float ballSpeed = 600.f;
	sf::Angle ballAngle;

	Paddle *playerOne = nullptr;
	Paddle *playerTwo = nullptr;

	sf::Clock delayClock;
	bool moveBall = false;

	// Random Number Generator
	std::random_device rando;
	std::mt19937 rng;
};

#endif // BALL_H