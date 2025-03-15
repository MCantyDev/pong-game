#include "drawables/Paddle.h"

Paddle::Paddle(PaddleSide side)
	: side(side)
{
	// Rect Setup
	rect.setSize(paddleSize - sf::Vector2f(4, 4));
	rect.setFillColor(sf::Color::White);
	// Outline Setup
	rect.setOutlineThickness(4);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOrigin({ (paddleSize.x / 2), (paddleSize.y / 2) });

	if (side == PaddleSide::LEFT)
		rect.setPosition({ 30.f, RenderWindowManager::GetHeight() / 2 });
	else if (side == PaddleSide::RIGHT)
		rect.setPosition({ RenderWindowManager::GetWidth() - 30.f, RenderWindowManager::GetHeight() / 2 });
	shape = &rect;
}

float Paddle::getTop() const
{
	return rect.getPosition().y - (paddleSize.y / 2);
}
float Paddle::getBottom() const
{
	return rect.getPosition().y + (paddleSize.y / 2);
}
float Paddle::getFront() const
{
	if (side == PaddleSide::LEFT)
		return rect.getPosition().x + (paddleSize.x / 2);

	return rect.getPosition().x - (paddleSize.x / 2);
}
float Paddle::getBack() const
{
	if (side == PaddleSide::LEFT)
		return rect.getPosition().x - (paddleSize.x / 2);

	return rect.getPosition().x + (paddleSize.x / 2);
}

bool Paddle::checkCollisions(const Drawable* object)
{
    if (side == PaddleSide::LEFT)
    {
		return (object->getBack() < getFront() && object->getBack() > getCenterX() &&
			object->getBottom() >= getTop() && object->getTop() <= getBottom());
    }
    else if (side == PaddleSide::RIGHT)
    {
		return (object->getFront() > getFront() && object->getFront() < getCenterX() &&
			object->getBottom() >= getTop() && object->getTop() <= getBottom());
    }
}

void Paddle::moveUp()
{
	if (getTop() > 10.f)
		rect.move({ 0.f, -paddleSpeed * DeltaTimeClock::GetDeltaTime() });
}

void Paddle::moveDown()
{
	if (getBottom() < RenderWindowManager::GetHeight() - 5.f)
	rect.move({ 0.f, paddleSpeed * DeltaTimeClock::GetDeltaTime() });
}
