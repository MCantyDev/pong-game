#ifndef RECTBUTTON_H
#define RECTBUTTON_H

#include "drawables/Button.h"

class RectButton : public Button
{
public:
	RectButton(std::string innerText, int fontSize, sf::Vector2f position, std::function<void()> onClick);

	// Pure Virtual Functions (overriden)
	virtual float getTop() const override;
	virtual float getBottom() const override;
	virtual float getLeft() const override;
	virtual float getRight() const override;

private:
	sf::RectangleShape rect;
	sf::Vector2f rectSize;
};

#endif // RECTBUTTON_H