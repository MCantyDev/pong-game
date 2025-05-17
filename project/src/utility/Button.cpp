#include "utility/Button.h"

sf::Font Button::font;

Button::Button(std::string innerText, int textSize, std::function<void()> onClickFunction)
	: buttonText(font, innerText, textSize), padding(10),
	onClick(std::move(onClickFunction))
{
	if (!font.openFromFile("fonts/MainFont.ttf"))
		throw std::runtime_error("Failed to Load font: fonts/MainFont.ttf");

	buttonText.setFillColor(sf::Color::Black);
}

void Button::checkClicked()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*RenderWindowManager::GetWindow());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && 
		(mousePos.y > getTop() && mousePos.y < getBottom()) &&
		(mousePos.x > getLeft() && mousePos.x < getRight()))
	{
		if (onClick)
			onClick();
	}
}

void Button::checkHovered()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*RenderWindowManager::GetWindow());

	if ((mousePos.y > getTop() && mousePos.y < getBottom()) &&
		(mousePos.x > getLeft() && mousePos.x < getRight()))
	{
		shape->setOutlineColor(sf::Color::Blue);
		return;
	}
	
	if (shape->getOutlineColor() == sf::Color::Blue)
		shape->setOutlineColor(sf::Color::Black);
}

void Button::draw(bool originVisable)
{
	RenderWindowManager::Draw(*shape);
	RenderWindowManager::Draw(buttonText);

	// Draw the Origin Point
	if (originVisable)
	{
		sf::CircleShape originMarker(3);
		originMarker.setFillColor(sf::Color::White);
		originMarker.setPosition({ shape->getPosition().x, shape->getPosition().y });
		originMarker.setOrigin({ 3, 3 });
		RenderWindowManager::Draw(originMarker);
	}
}