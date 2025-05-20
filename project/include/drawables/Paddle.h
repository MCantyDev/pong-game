#ifndef PADDLE_H
#define PADDLE_H

// SFML Include
#include "SFML/Graphics.hpp"

// Drawable Include
#include "drawables/Drawable.h"

#include "GameEnums.h"

/**
 * @class Paddle
 * @brief Represents a paddle in the Pong game, controlled by a player or AI.
 *
 * Inherits from Drawable and implements boundary positioning and movement functionality.
 * The Paddle can move vertically and detect collisions with other drawable objects,
 * such as the Ball. Each paddle is assigned a side (left or right).
 */
class Paddle : public Drawable
{
public:
	/**
	 * @brief Constructs a Paddle object for a given side.
	 * @param side Indicates whether the paddle belongs to the left or right player.
	 */
	Paddle(PaddleSide side);
	~Paddle() = default;

	virtual float getTop() const override;
	virtual float getBottom() const override;
	virtual float getLeft() const override;
	virtual float getRight() const override;

	/**
	 * @brief Checks for collision between this paddle and another drawable object (e.g., Ball).
	 * @param object Pointer to another drawable object.
	 * @return True if a collision is detected, false otherwise.
	 */
	bool checkCollisions(const Drawable *object);

	/**
	 * @brief Moves the paddle upward.
	 */
	void moveUp();

	/**
	 * @brief Moves the paddle downward.
	 */
	void moveDown();

protected:
	// Paddle Variables
	sf::RectangleShape rect;
	PaddleSide side;

	const sf::Vector2f paddleSize = sf::Vector2f(40, 120);
	float paddleSpeed = 500.f;
};

#endif // PADDLE_H