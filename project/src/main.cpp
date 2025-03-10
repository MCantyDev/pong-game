#define SFML_STATIC

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <iostream>

int main()
{
	const float WIDTH = 1200.0f; // Initial Window Width
	const float HEIGHT = 800.0f; // Initial Window Height
	bool isPlaying = false; // Current Game State
	sf::Clock clock; // Clock for DeltaTime

	// Graphics Constants
	const sf::Vector2f paddleSize(30, 100);
	const float paddleSpeed = 400.0f;
	const float ballSize = 10.0f;

	sf::RenderWindow window(sf::VideoMode({ (unsigned int)WIDTH, (unsigned int)HEIGHT }), "Pong Game", { sf::Style::Titlebar | sf::Style::Close });

	// Create Left Side Paddle
	sf::RectangleShape leftPaddle;
	leftPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
	leftPaddle.setOutlineThickness(3);
	leftPaddle.setOutlineColor(sf::Color::Black);
	leftPaddle.setFillColor(sf::Color(255, 50, 50));
	leftPaddle.setOrigin({ paddleSize.x / 2, paddleSize.y / 2 });

	// Create Right Side Paddle
	sf::RectangleShape rightPaddle;
	rightPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
	rightPaddle.setOutlineThickness(3);
	rightPaddle.setOutlineColor(sf::Color::Black);
	rightPaddle.setFillColor(sf::Color(50, 50, 255));
	rightPaddle.setOrigin({ paddleSize.x / 2, paddleSize.y / 2 });

	// Create the Ball
	sf::CircleShape ball;
	ball.setRadius(ballSize - 3);
	ball.setOutlineThickness(3);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin({ ballSize / 2, ballSize / 2 });
	

	sf::Font arial("fonts/Arial.ttf");

	sf::Text titleText(arial, "Pong the Game!", 30);
	sf::FloatRect titleTextBounds = titleText.getLocalBounds();
	titleText.setOrigin({titleTextBounds.size.x / 2, titleTextBounds.size.y / 2});

	titleText.setPosition({ WIDTH / 2, HEIGHT / 2 });


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
					// Start the game
					isPlaying = true;

					// Set Positions of everying
					leftPaddle.setPosition({ 30.0f, HEIGHT / 2 });
					rightPaddle.setPosition({ WIDTH - 30.0f, HEIGHT / 2 });
					ball.setPosition({ WIDTH / 2, HEIGHT / 2 });
				}
			}
		}

		if (isPlaying)
		{
			const float deltaTime = clock.restart().asSeconds();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && (leftPaddle.getPosition().y - (paddleSize.y / 2)) > 5.0f)
			{
				leftPaddle.move({ 0.f, -paddleSpeed * deltaTime });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && (leftPaddle.getPosition().y + (paddleSize.y / 2)) < HEIGHT - 5.0f)
			{
				leftPaddle.move({ 0.f, paddleSpeed * deltaTime });
			}
		}

		window.clear(sf::Color(50, 50, 50));

		if (isPlaying)
		{
			window.draw(leftPaddle);
			window.draw(rightPaddle);
			window.draw(ball);
		}
		else
		{
			window.draw(titleText);
		}
		window.display();
	}
}