#define SFML_STATIC

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <iostream>
#include <random>

int main()
{
	const float WIDTH = 1200.0f; // Initial Window Width
	const float HEIGHT = 800.0f; // Initial Window Height
	bool isPlaying = false; // Current Game State
	sf::Clock clock; // Clock for DeltaTime

	// Random Number Generator
	std::random_device rd;
	std::mt19937 rng(rd());

	// Paddles
	const sf::Vector2f paddleSize(30, 100);
	const float paddleSpeed = 500.0f;
	// Ball
	const float ballRadius = 10.0f;
	const float ballSpeed = 600.0f;
	sf::Angle ballAngle = sf::degrees(0); // Angle the Ball is moving in (Used for Y axis)
	// Score
	int leftScore = 0;
	int rightScore = 0;

	// Render Window
	sf::RenderWindow window(sf::VideoMode({ (unsigned int)WIDTH, (unsigned int)HEIGHT }), "Pong Game", { sf::Style::Titlebar | sf::Style::Close });

	// Create Left Side Paddle
	sf::RectangleShape redPaddle;
	redPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
	redPaddle.setOutlineThickness(3);
	redPaddle.setOutlineColor(sf::Color::Black);
	redPaddle.setFillColor(sf::Color(255, 50, 50));
	redPaddle.setOrigin({ paddleSize.x / 2, paddleSize.y / 2 });

	// Create Right Side Paddle
	sf::RectangleShape bluePaddle;
	bluePaddle.setSize(paddleSize - sf::Vector2f(3, 3));
	bluePaddle.setOutlineThickness(3);
	bluePaddle.setOutlineColor(sf::Color::Black);
	bluePaddle.setFillColor(sf::Color(50, 50, 255));
	bluePaddle.setOrigin({ paddleSize.x / 2, paddleSize.y / 2 });

	// Create the Ball
	sf::CircleShape ball;
	ball.setRadius(ballRadius - 3);
	ball.setOutlineThickness(3);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin({ ballRadius / 2, ballRadius / 2 });
	ball.setPosition({ WIDTH / 2, HEIGHT / 2 });
	
	// Load Font
	sf::Font arial("fonts/Arial.ttf");

	// Title Text
	sf::Text titleText(arial, "            Pong!\n\nPress Enter to Play!", 30);
	sf::FloatRect ttb = titleText.getLocalBounds();
	titleText.setOrigin({ ttb.size.x / 2, ttb.size.y / 2 });
	titleText.setPosition({ WIDTH / 2, HEIGHT / 2 });

	// Left Score Text
	sf::Text leftScoreText(arial, std::to_string(leftScore), 30);
	sf::FloatRect lstb = leftScoreText.getLocalBounds();
	leftScoreText.setOrigin({ lstb.size.x / 2, lstb.size.y / 2 });
	leftScoreText.setPosition({ WIDTH / 2 - 100, 50 });

	// Right Score Text
	sf::Text rightScoreText(arial, std::to_string(rightScore), 30);
	sf::FloatRect rstb = rightScoreText.getLocalBounds();
	rightScoreText.setOrigin({ rstb.size.x / 2, rstb.size.y / 2 });
	rightScoreText.setPosition({ WIDTH / 2 + 100, 50 });

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
					redPaddle.setPosition({ 30.0f, HEIGHT / 2 });
					bluePaddle.setPosition({ WIDTH - 30.0f, HEIGHT / 2 });
					ball.setPosition({ WIDTH / 2, HEIGHT / 2 });

					// Start the game
					isPlaying = true;
				}
			}
		}

		window.clear(sf::Color(50, 50, 50));
		const float deltaTime = clock.restart().asSeconds();

		if (isPlaying)
		{
			if (leftScore == 5 || rightScore == 5)
			{
				isPlaying = false;

				std::string wl = (leftScore == 5) ? "You Win!" : "You Lose!";
				titleText.setString("    Pong!\n\n" + wl);

				leftScore = 0;
				rightScore = 0;
				leftScoreText.setString("0");
				rightScoreText.setString("0");
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && (redPaddle.getPosition().y - (paddleSize.y / 2)) > 5.0f)
			{
				redPaddle.move({ 0.f, -paddleSpeed * deltaTime }); // Move ONLY on the Y Axis. Using negative speed gives us a negative number which will the be taken away from the Y value which moves us up 
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && (redPaddle.getPosition().y + (paddleSize.y / 2)) < HEIGHT - 5.0f)
			{
				redPaddle.move({ 0.f, paddleSpeed * deltaTime }); // Using normal speed gives u a positive number will will add to the Y value
			}

			// Move Ball by the value of Speed * Time for x value and the angle as the Y value
			ball.move({ ballSpeed * deltaTime, ballAngle });

			std::uniform_real_distribution<float> dist(0, 20);
			// Collision Checks
			// Score
			if (ball.getPosition().x - ballRadius < 0)
			{
				rightScoreText.setString(std::to_string(++rightScore));
				ball.setPosition({ WIDTH / 2, HEIGHT / 2 });
			}
			if (ball.getPosition().x + ballRadius >= WIDTH)
			{
				leftScoreText.setString(std::to_string(++leftScore));
				ball.setPosition({ WIDTH / 2, HEIGHT / 2 });
			}
			// Left Paddle
			if (ball.getPosition().x - ballRadius < redPaddle.getPosition().x + paddleSize.x / 2  && ball.getPosition().x - ballRadius > redPaddle.getPosition().x &&
				ball.getPosition().y + ballRadius >= redPaddle.getPosition().y - paddleSize.y / 2 && ball.getPosition().y - ballRadius <= redPaddle.getPosition().y + paddleSize.y / 2)
			{
				// These conditions will either give a slight upward angle or slight downward angle depending on whether the ball hit top or bottom of the paddle
				if (ball.getPosition().y > redPaddle.getPosition().y)
					ballAngle = sf::degrees(180) - ballAngle + sf::degrees(dist(rng));
				else
					ballAngle = sf::degrees(180) - ballAngle - sf::degrees(dist(rng));
				ball.setPosition({ redPaddle.getPosition().x + ballRadius + paddleSize.x / 2 + 0.1f, ball.getPosition().y });

			}
			// Right Paddle
			if (ball.getPosition().x + ballRadius > bluePaddle.getPosition().x - paddleSize.x / 2  && ball.getPosition().x + ballRadius < bluePaddle.getPosition().x &&
				ball.getPosition().y + ballRadius >= bluePaddle.getPosition().y - paddleSize.y / 2 && ball.getPosition().y - ballRadius <= bluePaddle.getPosition().y + paddleSize.y / 2)
			{
				// These conditions will either give a slight upward angle or slight downward angle depending on whether the ball hit top or bottom of the paddle
				if (ball.getPosition().y > bluePaddle.getPosition().y)
					ballAngle = sf::degrees(180) - ballAngle + sf::degrees(dist(rng));
				else
					ballAngle = sf::degrees(180) - ballAngle - sf::degrees(dist(rng));
				ball.setPosition({ bluePaddle.getPosition().x - ballRadius - paddleSize.x / 2 - 0.1f, ball.getPosition().y });
			}
			// Top Wall
			if (ball.getPosition().y - ballRadius < 0)
			{
				// Simply Invert the Balls Angle to flip the Y direction
				ballAngle = -ballAngle;
				ball.setPosition({ ball.getPosition().x, ball.getPosition().y + ballRadius + 0.1f });
			}
			// Bottom Wall
			if (ball.getPosition().y + ballRadius > HEIGHT)
			{
				// Simply Invert the Balls Angle to flip the Y direction
				ballAngle = -ballAngle;
				ball.setPosition({ ball.getPosition().x, ball.getPosition().y - ballRadius - 0.1f });
			}

			window.draw(redPaddle);
			window.draw(bluePaddle);
			window.draw(ball);

			window.draw(leftScoreText);
			window.draw(rightScoreText);
		}
		else
		{
			window.draw(titleText);
		}
		window.display();
	}
}