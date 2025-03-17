#include "utility/RectButton.h"

RectButton::RectButton(std::string innerText, int fontSize, sf::Vector2f position)
    : Button(innerText, fontSize)
{
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    sf::Vector2f textSize(textBounds.size.x, textBounds.size.y);

    float paddingX = textSize.x * 0.1f;
    float paddingY = textSize.y * 0.2f;

    sf::Vector2f paddingVector(paddingX, paddingY);
    rectSize = textSize + paddingVector * 2.0f;

    rect.setSize(rectSize);

    rect.setFillColor(sf::Color::White);
    rect.setOutlineThickness(4);
    rect.setOutlineColor(sf::Color::Black);

    rect.setOrigin({ rectSize.x / 2, rectSize.y / 2 });
    rect.setPosition(position);

    buttonText.setOrigin({ textBounds.size.x / 2, textBounds.size.y / 2 });
    buttonText.setPosition(position);

    shape = &rect;
}

float RectButton::getTop() const
{
	return rect.getPosition().y - (rectSize.y / 2);
}
float RectButton::getBottom() const
{
	return rect.getPosition().y + (rectSize.y / 2);
}
float RectButton::getLeft() const
{
	return rect.getPosition().x - (rectSize.x / 2);
}
float RectButton::getRight() const
{
	return rect.getPosition().x + (rectSize.x / 2);
}