#include "state/PlayingState.h"

// Different State Types
#include "state/MenuState.h"

PlayingState::PlayingState(StateManager* manager)
	: State(manager), window(manager->getWindow()),
	rando(), rng(rando())
{
	width = window.getSize().x;
	height = window.getSize().y;

	initialisePaddles();
	initialiseBall();
	initialiseSounds();
}

void PlayingState::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		stateManager->changeState(new MenuState(stateManager));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && (leftPaddle.getPosition().y - (paddleSize.y / 2)) > 10.f)
	{
		leftPaddle.move({ 0.f, -paddleSpeed * deltaTime });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && (leftPaddle.getPosition().y + (paddleSize.y / 2)) < height - 5.f)
	{
		leftPaddle.move({ 0.f, paddleSpeed * deltaTime });
	}
}

void PlayingState::update()
{
	deltaTime = DeltaTimeClock::getDeltaTime();

	if (delayClock.getElapsedTime() > sf::seconds(1))
	{
		moveBall = true;
		delayClock.stop();
	}

	if (leftScore == 5 || rightScore == 5)
		stateManager->changeState(new MenuState(stateManager));

	if (moveBall)
		ball.move({ ballSpeed * deltaTime, ballAngle });

	moveAI();
	checkPaddleCollisions();
	checkWallCollisions();
	checkScored();
}

void PlayingState::render()
{
	window.draw(leftPaddle);
	window.draw(rightPaddle);
	window.draw(ball);
}

void PlayingState::moveAI()
{
	if ((rightPaddle.getPosition().y - (paddleSize.y / 2) > 10.0f) &&
		(rightPaddle.getPosition().y + (paddleSize.y / 2) < height - 5.0f))
	{
		rightPaddle.move({ 0.0f, computerPaddleSpeed * deltaTime });
		if (rightPaddle.getPosition().y - (paddleSize.y / 2) < 10.0f) { rightPaddle.setPosition({ (width - 30.0f), ((paddleSize.y / 2) + 10.1f) }); }
		else if (rightPaddle.getPosition().y + (paddleSize.y / 2) > height - 5.0f) { rightPaddle.setPosition({ (width - 30.0f), (height - (paddleSize.y / 2) - 5.1f) }); }
	}

	if (computerClock.getElapsedTime() > computerTime)
	{
		computerClock.restart();
		if (ball.getPosition().y + ballRadius > rightPaddle.getPosition().y + (paddleSize.y / 2)) { computerPaddleSpeed = paddleSpeed; }
		else if (ball.getPosition().y - ballRadius < rightPaddle.getPosition().y - (paddleSize.y / 2)) { computerPaddleSpeed = -paddleSpeed; }
		else { computerPaddleSpeed = 0.0f; }
	}
}

void PlayingState::checkPaddleCollisions()
{
	std::uniform_real_distribution<float> dist(0, 20); // 20 is a Massive Angle in this game as the perfect angle range is only around 90 degrees
	if (ball.getPosition().x - ballRadius < leftPaddle.getPosition().x + (paddleSize.x / 2) && ball.getPosition().x - ballRadius > leftPaddle.getPosition().x &&
		ball.getPosition().y + ballRadius >= leftPaddle.getPosition().y - (paddleSize.y / 2) && ball.getPosition().y - ballRadius <= leftPaddle.getPosition().y + (paddleSize.y / 2))
	{
		paddleBounce.play();

		if (ball.getPosition().y > leftPaddle.getPosition().y)
			ballAngle = sf::degrees(180) - ballAngle + sf::degrees(dist(rng));
		else
			ballAngle = sf::degrees(180) - ballAngle - sf::degrees(dist(rng));
		ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.f, 360.f) - 180.f);
		ball.setPosition({ leftPaddle.getPosition().x + ballRadius + (paddleSize.x / 2) + 0.1f, ball.getPosition().y });
	}

	if (ball.getPosition().x + ballRadius > rightPaddle.getPosition().x - (paddleSize.x / 2) && ball.getPosition().x + ballRadius < rightPaddle.getPosition().x &&
		ball.getPosition().y + ballRadius >= rightPaddle.getPosition().y - (paddleSize.y / 2) && ball.getPosition().y - ballRadius <= rightPaddle.getPosition().y + (paddleSize.y / 2))
	{
		paddleBounce.play();

		if (ball.getPosition().y > rightPaddle.getPosition().y)
			ballAngle = sf::degrees(180) - ballAngle + sf::degrees(dist(rng));
		else
			ballAngle = sf::degrees(180) - ballAngle - sf::degrees(dist(rng));
		ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.f, 360.f) - 180.f);
		ball.setPosition({ rightPaddle.getPosition().x - ballRadius - (paddleSize.x / 2) - 0.1f, ball.getPosition().y });
	}
}

void PlayingState::checkWallCollisions()
{
	if (ball.getPosition().y - ballRadius < 0)
	{
		wallBounce.play();

		ballAngle = -ballAngle;
		ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.f, 360.f) - 180.f);
		ball.setPosition({ ball.getPosition().x, ball.getPosition().y + ballRadius + 0.1f });
	}

	if (ball.getPosition().y + ballRadius > height)
	{
		wallBounce.play();

		ballAngle = -ballAngle;
		ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.f, 360.f) - 180.f);
		ball.setPosition({ ball.getPosition().x, ball.getPosition().y - ballRadius - 0.1f });
	}
}

void PlayingState::checkScored()
{
	if (ball.getPosition().x - ballRadius < 0)
	{
		scorePoint.play();
		rightScore++;

		moveBall = false;
		delayClock.restart();

		ball.setPosition({ width / 2, height / 2 });

		std::uniform_real_distribution<float> dist(135, 225);
		ballAngle = sf::degrees(fmod(dist(rng) + 180.f, 360.f) - 180.f);
	}

	if (ball.getPosition().x + ballRadius > width)
	{
		scorePoint.play();
		leftScore++;

		moveBall = false;
		delayClock.restart();

		ball.setPosition({ width / 2, height / 2 });

		std::uniform_real_distribution<float> dist(-45, 45);
		ballAngle = sf::degrees(fmod(dist(rng) + 180.f, 360.f) - 180.f);
	}
}

void PlayingState::initialisePaddles()
{
	// Left Paddle
	leftPaddle.setSize(paddleSize - sf::Vector2f(4, 4));
	leftPaddle.setFillColor(sf::Color(200, 50, 50));
	leftPaddle.setOutlineThickness(4);
	leftPaddle.setOutlineColor(sf::Color::Black);
	leftPaddle.setOrigin({ paddleSize.x / 2, paddleSize.y / 2 });
	leftPaddle.setPosition({ 30.f, height / 2 });

	// Right Paddle
	rightPaddle.setSize(paddleSize - sf::Vector2f(4, 4));
	rightPaddle.setFillColor(sf::Color(50, 50, 200));
	rightPaddle.setOutlineThickness(4);
	rightPaddle.setOutlineColor(sf::Color::Black);
	rightPaddle.setOrigin({ paddleSize.x / 2, paddleSize.y / 2 });
	rightPaddle.setPosition({ width - 30.f, height / 2 });
}

void PlayingState::initialiseBall()
{
	// Ball
	ball.setRadius(ballRadius - 4);
	ball.setFillColor(sf::Color::White);
	ball.setOutlineThickness(4);
	ball.setOutlineColor(sf::Color::Black);
	ball.setOrigin({ ballRadius / 2, ballRadius / 2 });
	ball.setPosition({ width / 2, height / 2 });
}

void PlayingState::initialiseSounds()
{
	if (paddleBounceBuffer.loadFromFile("sounds/paddle_bounce.wav"))
	if (wallBounceBuffer.loadFromFile("sounds/wall_bounce.wav"))
	if (scorePointBuffer.loadFromFile("sounds/score_point.wav"))

	paddleBounce.setVolume(10);
	wallBounce.setVolume(10);
	scorePoint.setVolume(10);
}