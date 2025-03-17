#ifndef PADDLE_H
#define PADDLE_H

// SFML Include
#include "SFML/Graphics.hpp"

// Drawable Include
#include "drawables/Drawable.h"

enum class PaddleSide
{
	LEFT,
	RIGHT
};

class Paddle : public Drawable
{
public:
	Paddle(PaddleSide side);
	~Paddle() = default;

	virtual float getTop() const override;
	virtual float getBottom() const override;
	virtual float getLeft() const override;
	virtual float getRight() const override;

	// What Paddle Needs to be able to do
	// - Move Up
	// - Move Down
	// - Check for Collisions against a Ball
	//
	bool checkCollisions(const Drawable* object);
	
	void moveUp();
	void moveDown();

protected:
	// Paddle Variables
	sf::RectangleShape rect;
	PaddleSide side;

	const sf::Vector2f paddleSize = sf::Vector2f(40, 120);
	float paddleSpeed = 500.f;
};

#endif // PADDLE_H