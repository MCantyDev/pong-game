#ifndef BUTTON_H
#define BUTTON_H

// SFML Include
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "drawables/Drawable.h"

// Standard Library Include
#include <functional>

/**
 * @class Button
 * @brief Represents a clickable UI button in the Pong game menu or settings.
 *
 * Abstract class that inherits from Drawable and implements interaction detection such as clicking and hovering.
 * The Button stores its display text and a function to be executed on click.
 */
class Button : public Drawable
{
public:
	/**
	 * @brief Constructs a Button with text, font size, and a callback function.
	 * @param innerText The text displayed on the button.
	 * @param textSize The font size of the button text.
	 * @param onClickFunction The function to call when the button is clicked.
	 */
	Button(std::string innerText, int textSize, std::function<void()> onClickFunction);

	/**
	 * @brief Checks if the button has been clicked by the user and executes its click function if so.
	 */
	void checkClicked();

	/**
	 * @brief Checks if the button is currently being hovered over by the mouse.
	 * Updates visual state accordingly.
	 */
	void checkHovered();

	/**
	 * @brief Renders the button to the screen.
	 * @param originVisable If true, the origin of the button will be visually marked (for debugging).
	 */
	virtual void draw(bool originVisable = false) override;

	// Pure Virtual Functions (overriden)
	virtual float getTop() const = 0;
	virtual float getBottom() const = 0;
	virtual float getLeft() const = 0;
	virtual float getRight() const = 0;

private:
	std::function<void()> onClick;

protected:
	// Button properties
	sf::Text buttonText;
	static sf::Font font;
	int padding; // Percentage based
};

#endif // BUTTON_H