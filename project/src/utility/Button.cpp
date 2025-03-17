#include "utility/Button.h"

Button::Button(std::string innerText, int textSize)
	: buttonText(font, innerText, textSize), padding(10)
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
		(mousePos.x > getLeft() && mousePos.y < getRight()))
	{
		if (!this->onClick)
			throw std::runtime_error("Please Set Function for Button");

		onClick();
	}
}

void Button::checkHovered()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*RenderWindowManager::GetWindow());

	if ((mousePos.y > getTop() && mousePos.y < getBottom()) &&
		(mousePos.x > getLeft() && mousePos.y < getRight()))
	{
		shape->setOutlineColor(sf::Color::Blue);
		return;
	}
	
	if (shape->getOutlineColor() == sf::Color::Blue)
		shape->setOutlineColor(sf::Color::Black);
}

void Button::setOnClick(std::function<void()> onClickFunction)
{
	this->onClick = onClickFunction;
}

void Button::draw(bool originVisable)
{
	RenderWindowManager::GetWindow()->draw(*shape);
	RenderWindowManager::GetWindow()->draw(buttonText);

	// Draw the Origin Point
	if (originVisable)
	{
		sf::CircleShape originMarker(3);
		originMarker.setFillColor(sf::Color::White);
		originMarker.setPosition({ shape->getPosition().x, shape->getPosition().y });
		originMarker.setOrigin({ 3, 3 });
		RenderWindowManager::GetWindow()->draw(originMarker);
	}
}