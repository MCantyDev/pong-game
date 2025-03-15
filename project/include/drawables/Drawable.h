#ifndef DRAWABLE_H
#define DRAWABLE_H

// SFML Include
#include "SFML/Graphics.hpp"

// Custom Include
#include "RenderWindowManager.h"

class Drawable
{
public:
	virtual ~Drawable();

	// Move Functions
	void move(const sf::Vector2f& offset);
	void setPosition(const sf::Vector2f& position);

	// Get Positional Data - Pure Virtual Functions
	virtual float getTop() const = 0;
	virtual float getBottom() const = 0;
	virtual float getFront() const = 0;
	virtual float getBack() const = 0;

	// Get Center Position Functions
	sf::Vector2f getCenter() const;
	float getCenterX() const;
	float getCenterY() const;

	// Colour Functions
	void setColour(const sf::Color& color);
	void setOutline(float thickness, const sf::Color& color);

	void draw(bool originVisable = false);

protected:
	sf::Shape* shape = nullptr; // Flexible Shape pointer

private:
	sf::RenderWindow* window = RenderWindowManager::GetWindow();
};

#endif // DRAWABLE_H