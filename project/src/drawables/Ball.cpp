#include "drawables/Ball.h"

#include "drawables/Paddle.h"

Ball::Ball(Paddle* p1, Paddle* p2)
	: playerOne(p1), playerTwo(p2),
	rando(), rng(rando()), scoreManager(ScoreManager::GetInstance())
{
	circle.setRadius(ballRadius - 4);
	circle.setFillColor(sf::Color::White);
	circle.setOutlineThickness(4);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOrigin({ ballRadius / 2, ballRadius / 2 });
	circle.setPosition({ RenderWindowManager::GetWidth() / 2, RenderWindowManager::GetHeight() / 2 });
	shape = &circle;

	// Add an Observer
	addObserver(scoreManager);

	// Choose Random Starting Angle
	double r = ((double)rand() / (RAND_MAX));
	std::uniform_real_distribution<float> dist;

	if (r > 0.5)
		dist = std::uniform_real_distribution<float>(135, 225);
	else
		dist = std::uniform_real_distribution<float>(-45, 45);

	ballAngle = sf::degrees(fmod(dist(rng) + 180.0f, 360.f) - 180.f);
}

void Ball::update()
{
	if (!moveBall)
	{
		if (delayClock.getElapsedTime() > sf::seconds(1))
		{
			moveBall = true;
			delayClock.stop();
		}
		else return;
	}
	// Check Collisions
	paddleCollisionCheck();
	wallCollisionCheck();
	scoreCollisionCheck();

	// Move Ball
	circle.move({ ballSpeed * DeltaTimeClock::GetDeltaTime(), ballAngle });

}

void Ball::paddleCollisionCheck()
{
	if (playerOne->checkCollisions(this))
	{
		SoundManager::GetSound("paddle_bounce")->play();
		std::uniform_real_distribution<float> dist(0, 20);
		ballAngle = sf::degrees(180) - ballAngle;

		if (circle.getPosition().y > playerOne->getCenterY())
			ballAngle += sf::degrees(dist(rng));
		else if (circle.getPosition().y < playerOne->getCenterY())
			ballAngle -= sf::degrees(dist(rng));

		ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.f, 360.f) - 180.f);
		circle.setPosition({ circle.getPosition().x + ballRadius + 0.1f, circle.getPosition().y });
	}

	if (playerTwo->checkCollisions(this))
	{
		SoundManager::GetSound("paddle_bounce")->play();
		std::uniform_real_distribution<float> dist(0, 20);
		ballAngle = sf::degrees(180) - ballAngle;

		if (circle.getPosition().y > playerTwo->getCenterY())
			ballAngle += sf::degrees(dist(rng));
		else if (circle.getPosition().y < playerTwo->getCenterY())
			ballAngle -= sf::degrees(dist(rng));

		ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.f, 360.f) - 180.f);
		circle.setPosition({ circle.getPosition().x - ballRadius - 0.1f, circle.getPosition().y });
	}
}
void Ball::wallCollisionCheck()
{
	if (circle.getPosition().y - ballRadius < 0)
	{
		SoundManager::GetSound("wall_bounce")->play();
		ballAngle = -ballAngle;
		ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.f, 360.f) - 180.f);
		circle.setPosition({ circle.getPosition().x, circle.getPosition().y + ballRadius + 0.1f });
	}

	if (circle.getPosition().y + ballRadius > RenderWindowManager::GetHeight())
	{
		SoundManager::GetSound("wall_bounce")->play();
		ballAngle = -ballAngle;
		ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.f, 360.f) - 180.f);
		circle.setPosition({ circle.getPosition().x, circle.getPosition().y - ballRadius - 0.1f });
	}
}
void Ball::scoreCollisionCheck()
{
	if (circle.getPosition().x - ballRadius < 0.f)
	{
		SoundManager::GetSound("score_point")->play();
		notifyObservers(PaddleSide::RIGHT);

		delayClock.restart();
		moveBall = false;

		// Reset Position
		circle.setPosition({ RenderWindowManager::GetWidth() / 2, RenderWindowManager::GetHeight() / 2 });

		// Random Angle
		std::uniform_real_distribution<float> dist(135, 225);
		ballAngle = sf::degrees(fmod(dist(rng) + 180.0f, 360.f) - 180.f);
	}

	if (circle.getPosition().x + ballRadius > RenderWindowManager::GetWidth())
	{
		SoundManager::GetSound("score_point")->play();
		notifyObservers(PaddleSide::LEFT);

		delayClock.restart();
		moveBall = false;

		// Reset Position
		circle.setPosition({ RenderWindowManager::GetWidth() / 2, RenderWindowManager::GetHeight() / 2 });

		// Random Angle
		std::uniform_real_distribution<float> dist(-45, 45);
		ballAngle = sf::degrees(fmod(dist(rng) + 180.0f, 360.f) - 180.f);
	}
}

float Ball::getTop() const
{
	return circle.getPosition().y - ballRadius;
}

float Ball::getBottom() const
{
	return circle.getPosition().y + ballRadius;
}

float Ball::getLeft() const
{
	return circle.getPosition().x - ballRadius;
}

float Ball::getRight() const
{
	return circle.getPosition().x + ballRadius;
}