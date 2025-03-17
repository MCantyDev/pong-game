#ifndef BUTTON_H
#define BUTTON_H

// SFML Include
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "drawables/Drawable.h"

// Standard Library Include
#include <functional>

class Button : public Drawable
{
public:
	Button(std::string innerText, int textSize);

	void checkClicked();
	void checkHovered();
	void setOnClick(std::function<void()> onClickFunction);

	// Pure Virtual Functions (overriden)
	virtual float getTop() const = 0;
	virtual float getBottom() const = 0;
	virtual float getLeft() const = 0;
	virtual float getRight() const = 0;

	virtual void draw(bool originVisable = false) override;

private:
	std::function<void()> onClick;
	
protected:
	// Button properties
	sf::Text buttonText;
	sf::Font font;
	int padding; // Percentage based
};

#endif // BUTTON_H