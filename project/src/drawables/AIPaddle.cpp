#include "drawables/AIPaddle.h"

AiPaddle::AiPaddle(PaddleSide side)
	: Paddle(side)
{
	// AI Paddle Speed starts at 0
	paddleSpeed = 0.f;
}

void AiPaddle::update()
{
	if (object == nullptr)
		throw std::runtime_error("Set object for AI Paddle to track with [aiPaddle] setObject() function");

	calcSpeed(object);

	move({ 0.f, paddleSpeed * DeltaTimeClock::GetDeltaTime() });

	if (getTop() < 10.f)
		setPosition({ RenderWindowManager::GetWidth() - 30.f, 10.f + (paddleSize.y / 2) + 0.1f});
	else if (getBottom() > RenderWindowManager::GetHeight() - 5.f)
		setPosition({ RenderWindowManager::GetWidth() - 30.f, (RenderWindowManager::GetHeight() - 5.f) - (paddleSize.y / 2) - 0.1f });
}

void AiPaddle::setObject(Drawable* object)
{
	this->object = object;
}

void AiPaddle::calcSpeed(Drawable* object)
{
	computerClock.restart();

	if (object->getBottom() > getBottom())
		paddleSpeed = 500.f;
	else if (object->getTop() < getTop())
		paddleSpeed = -500.f;
	else
		paddleSpeed = 0.f;
}