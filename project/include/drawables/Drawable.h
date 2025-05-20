#ifndef DRAWABLE_H
#define DRAWABLE_H

// SFML Include
#include "SFML/Graphics.hpp"

// Core Include
#include "core/RenderWindowManager.h"
#include "core/DeltaTimeClock.h"

/**
 * @class Drawable
 * @brief Abstract base class representing drawable game objects with positioning and rendering logic.
 *
 * This class provides a general interface and common functionality for all game objects that can be drawn
 * to the screen and manipulated within the game world. It includes movement operations, position querying,
 * and utility rendering options.
 *
 * Subclasses must implement positional boundary methods used for collision detection or layout.
 */
class Drawable
{
public:
	/**
	 * @brief Virtual destructor.
	 */
	virtual ~Drawable();

	// Movement
	/**
	 * @brief Moves the drawable object by the specified offset.
	 * @param offset A 2D vector representing how far to move in x and y directions.
	 */
	void move(const sf::Vector2f &offset);

	/**
	 * @brief Sets the position of the drawable object.
	 * @param position The new position as an sf::Vector2f.
	 */
	void setPosition(const sf::Vector2f &position);

	// Pure virtual boundary accessors
	/**
	 * @brief Gets the top position of the object.
	 * @return A float representing the top edge's y-coordinate.
	 */
	virtual float getTop() const = 0;

	/**
	 * @brief Gets the bottom position of the object.
	 * @return A float representing the bottom edge's y-coordinate.
	 */
	virtual float getBottom() const = 0;

	/**
	 * @brief Gets the left position of the object.
	 * @return A float representing the left edge's x-coordinate.
	 */
	virtual float getLeft() const = 0;

	/**
	 * @brief Gets the right position of the object.
	 * @return A float representing the right edge's x-coordinate.
	 */
	virtual float getRight() const = 0;

	/**
	 * @brief Draws the object. Optionally, the origin point can be made visible.
	 * @param originVisible If true, renders a visual marker at the object's origin.
	 */
	virtual void draw(bool originVisible = false);
	
	// Center position utilities
	/**
	 * @brief Gets the center of the object as a 2D vector.
	 * @return sf::Vector2f representing the center (x, y).
	 */
	sf::Vector2f getCenter() const;

	/**
	 * @brief Gets the x-coordinate of the object's center.
	 * @return A float representing the center x position.
	 */
	float getCenterX() const;

	/**
	 * @brief Gets the y-coordinate of the object's center.
	 * @return A float representing the center y position.
	 */
	float getCenterY() const;

	// Appearance
	/**
	 * @brief Sets the fill color of the drawable object.
	 * @param color The SFML color to apply.
	 */
	void setColour(const sf::Color &color);

	/**
	 * @brief Sets the outline thickness and color of the object.
	 * @param thickness Outline thickness.
	 * @param color Outline color.
	 */
	void setOutline(float thickness, const sf::Color &color);


protected:
	sf::Shape *shape = nullptr; // Flexible Shape pointer
};

#endif // DRAWABLE_H