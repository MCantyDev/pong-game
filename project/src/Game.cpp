#include "Game.h"

Game::Game()
	: rando(), rng(rando()),
	window(sf::VideoMode({ (unsigned int)WIDTH, (unsigned int)HEIGHT }), title, { sf::Style::Titlebar | sf::Style::Close })
{
	std::cout << "Game Created" << std::endl;
	window.setVerticalSyncEnabled(true);

	initialisePaddles();
	initialiseBall();
	initialiseSounds();

	backgroundMusic.play();
}

Game::~Game()
{
	std::cout << "Game Ended" << std::endl;
}

void Game::run()
{
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>() ||
				event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
			{
				window.close();
				break;
			}

			if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter)
			{
				if (isPlaying == false)
				{
					// Set Positions of everying
					leftPaddle.setPosition({ 30.0f, HEIGHT / 2 });
					rightPaddle.setPosition({ WIDTH - 30.0f, HEIGHT / 2 });
					ball.setPosition({ WIDTH / 2, HEIGHT / 2 });

					// Start the game
					isPlaying = true;
					delayClock.restart();
				}
			}
		}
		window.clear(sf::Color(50, 50, 50));
		const float deltaTime = clock.restart().asSeconds();

		if (isPlaying)
		{
			if (delayClock.getElapsedTime() > sf::seconds(1))
			{
				moveBall = true; // Allow ball movement
				delayClock.stop(); // Stop the Delay clock as we dont need to count up anymore so no reason not to stop it
			}

			if (leftScore == 5 || rightScore == 5)
			{
				isPlaying = false;
				ballAngle = sf::degrees(0);
				leftScore = 0;
				rightScore = 0;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && (leftPaddle.getPosition().y - (paddleSize.y / 2)) > 10.0f)
				leftPaddle.move({ 0.0f, -paddleSpeed * deltaTime }); // Move ONLY on the Y Axis. Using negative speed gives us a negative number which will the be taken away from the Y value which moves us up 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && (leftPaddle.getPosition().y + (paddleSize.y / 2)) < HEIGHT - 5.0f)
				leftPaddle.move({ 0.0f, paddleSpeed * deltaTime }); // Using normal speed gives u a positive number will will add to the Y value

			if ((rightPaddle.getPosition().y - (paddleSize.y / 2) > 10.0f) &&
				(rightPaddle.getPosition().y + (paddleSize.y / 2) < HEIGHT - 5.0f))
			{
				rightPaddle.move({ 0.0f, computerPaddleSpeed * deltaTime });
				if (rightPaddle.getPosition().y - (paddleSize.y / 2) < 10.0f) { rightPaddle.setPosition({ (WIDTH - 30.0f), ((paddleSize.y / 2) + 10.1f) }); }
				else if (rightPaddle.getPosition().y + (paddleSize.y / 2) > HEIGHT - 5.0f) { rightPaddle.setPosition({ (WIDTH - 30.0f), (HEIGHT - (paddleSize.y / 2) - 5.1f) }); }
			}

			if (computerClock.getElapsedTime() > computerTime)
			{
				computerClock.restart();
				if (ball.getPosition().y + ballRadius > rightPaddle.getPosition().y + (paddleSize.y / 2)) { computerPaddleSpeed = paddleSpeed; }
				else if (ball.getPosition().y - ballRadius < rightPaddle.getPosition().y - (paddleSize.y / 2)) { computerPaddleSpeed = -paddleSpeed; }
				else { computerPaddleSpeed = 0.0f; }
			}

			if (moveBall) ball.move({ ballSpeed * deltaTime, ballAngle });

			// Scoring
			if (ball.getPosition().x - ballRadius < 0)
			{
				scorePoint.play();
				// Stop Ball from Moving
				moveBall = false;
				delayClock.restart();

				ball.setPosition({ WIDTH / 2, HEIGHT / 2 });

				// Random Angle
				std::uniform_real_distribution<float> dist(135, 225);
				ballAngle = sf::degrees(fmod(dist(rng) + 180.0f, 360.0f) - 180.0f);
			}
			if (ball.getPosition().x + ballRadius >= WIDTH)
			{
				scorePoint.play();
				// Stop Ball from Moving
				moveBall = false;
				delayClock.restart();

				ball.setPosition({ WIDTH / 2, HEIGHT / 2 });

				std::uniform_real_distribution<float> dist(-45, 45);
				ballAngle = sf::degrees(fmod(dist(rng) + 180.0f, 360.0f) - 180.0f);
			}

			// Collision Check for Paddles, Top Wall and Bottom Wall
			std::uniform_real_distribution<float> dist(0, 20);
			// Left Paddle
			if (ball.getPosition().x - ballRadius < leftPaddle.getPosition().x + paddleSize.x / 2 && ball.getPosition().x - ballRadius > leftPaddle.getPosition().x &&
				ball.getPosition().y + ballRadius >= leftPaddle.getPosition().y - paddleSize.y / 2 && ball.getPosition().y - ballRadius <= leftPaddle.getPosition().y + paddleSize.y / 2)
			{
				paddleBounce.play();
				// These conditions will either give a slight upward angle or slight downward angle depending on whether the ball hit top or bottom of the paddle
				if (ball.getPosition().y > leftPaddle.getPosition().y)
					ballAngle = sf::degrees(180) - ballAngle + sf::degrees(dist(rng));
				else
					ballAngle = sf::degrees(180) - ballAngle - sf::degrees(dist(rng));
				ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.0f, 360.0f) - 180.0f);
				ball.setPosition({ leftPaddle.getPosition().x + ballRadius + paddleSize.x / 2 + 0.1f, ball.getPosition().y });
			}
			// Right Paddle
			if (ball.getPosition().x + ballRadius > rightPaddle.getPosition().x - paddleSize.x / 2 && ball.getPosition().x + ballRadius < rightPaddle.getPosition().x &&
				ball.getPosition().y + ballRadius >= rightPaddle.getPosition().y - paddleSize.y / 2 && ball.getPosition().y - ballRadius <= rightPaddle.getPosition().y + paddleSize.y / 2)
			{
				paddleBounce.play();
				// These conditions will either give a slight upward angle or slight downward angle depending on whether the ball hit top or bottom of the paddle
				if (ball.getPosition().y > rightPaddle.getPosition().y)
					ballAngle = sf::degrees(180) - ballAngle + sf::degrees(dist(rng));
				else
					ballAngle = sf::degrees(180) - ballAngle - sf::degrees(dist(rng));
				ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.0f, 360.0f) - 180.0f);
				ball.setPosition({ rightPaddle.getPosition().x - ballRadius - paddleSize.x / 2 - 0.1f, ball.getPosition().y });
			}
			// Top Wall
			if (ball.getPosition().y - ballRadius < 0)
			{
				// Simply Invert the Balls Angle to flip the Y direction
				wallBounce.play();
				ballAngle = -ballAngle;
				ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.0f, 360.0f) - 180.0f);
				ball.setPosition({ ball.getPosition().x, ball.getPosition().y + ballRadius + 0.1f });
			}
			// Bottom Wall
			if (ball.getPosition().y + ballRadius > HEIGHT)
			{
				// Simply Invert the Balls Angle to flip the Y direction
				wallBounce.play();
				ballAngle = -ballAngle;
				ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.0f, 360.0f) - 180.0f);
				ball.setPosition({ ball.getPosition().x, ball.getPosition().y - ballRadius - 0.1f });
			}

			window.draw(leftPaddle);
			window.draw(rightPaddle);
			window.draw(ball);
		}
		window.display();
	}
}

void Game::initialisePaddles()
{
	// Left Paddle
	leftPaddle.setSize(paddleSize - sf::Vector2f(4, 4));
	leftPaddle.setFillColor(sf::Color(200, 50, 50));
	leftPaddle.setOutlineThickness(4);
	leftPaddle.setOutlineColor(sf::Color::Black);
	leftPaddle.setOrigin({ paddleSize.x / 2, paddleSize.y / 2 });

	// Right Paddle
	rightPaddle.setSize(paddleSize - sf::Vector2f(4, 4));
	rightPaddle.setFillColor(sf::Color(50, 50, 200));
	rightPaddle.setOutlineThickness(4);
	rightPaddle.setOutlineColor(sf::Color::Black);
	rightPaddle.setOrigin({ paddleSize.x / 2, paddleSize.y / 2 });
}

void Game::initialiseBall()
{
	// Ball
	ball.setRadius(ballRadius - 4);
	ball.setFillColor(sf::Color::White);
	ball.setOutlineThickness(4);
	ball.setOutlineColor(sf::Color::Black);
	ball.setOrigin({ ballRadius / 2, ballRadius / 2 });
}

void Game::initialiseSounds()
{
	paddleBounceBuffer.loadFromFile("sounds/paddle_bounce.wav");
	wallBounceBuffer.loadFromFile("sounds/wall_bounce.wav");
	scorePointBuffer.loadFromFile("sounds/score_point.wav");
	backgroundMusic.openFromFile("sounds/background_music.mp3");

	paddleBounce.setVolume(10);
	wallBounce.setVolume(10);
	scorePoint.setVolume(10);
	backgroundMusic.setVolume(15);

}
