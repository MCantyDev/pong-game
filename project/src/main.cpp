#define SFML_STATIC

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

#include <iostream>
#include <cmath>
#include <random>

int main()
{
	// Base Values
	const float WIDTH = 1200.0f; // Initial Window Width
	const float HEIGHT = 800.0f; // Initial Window Height
	bool isPlaying = false; // Current Game State
	sf::Clock clock; // Clock for DeltaTime

	// Delay Movement after Start and Scored Point
	sf::Clock moveDelay;
	bool moveBall = false;

	// Computer / AI Player (Dont even try to beat this man for he is Speed!)
	sf::Clock computerClock;
	sf::Time computerTime(sf::milliseconds(1));
	float computerPaddleSpeed = 0.0f;
 
	// Random Number Generator
	std::random_device rando;
	std::mt19937 rng(rando());

	// Paddles
	const sf::Vector2f paddleSize(40, 120);
	const float paddleSpeed = 500.0f;
	// Ball
	const float ballRadius = 15.0f;
	const float ballSpeed = 600.0f;
	sf::Angle ballAngle = sf::degrees(-180); // Angle the Ball is moving in (Used for Y axis)

	// Score
	int leftScore = 0;
	int rightScore = 0;

	// Render Window
	sf::RenderWindow window(sf::VideoMode({ (unsigned int)WIDTH, (unsigned int)HEIGHT }), "Pong Game", { sf::Style::Titlebar | sf::Style::Close });
	window.setVerticalSyncEnabled(true);

	// Shapes!
	// Create Left Side Paddle
	sf::RectangleShape redPaddle;
	redPaddle.setSize(paddleSize - sf::Vector2f(4, 4)); // Have to remove some to account for the Outline
	redPaddle.setOutlineThickness(4);
	redPaddle.setOutlineColor(sf::Color::Black);
	redPaddle.setFillColor(sf::Color(255, 50, 50)); 
	redPaddle.setOrigin({ paddleSize.x / 2, paddleSize.y / 2 }); // Setting the Origin to the Center of the paddle instead of the Top Left most point

	// Create Right Side Paddle
	sf::RectangleShape bluePaddle;
	bluePaddle.setSize(paddleSize - sf::Vector2f(4, 4));
	bluePaddle.setOutlineThickness(4);
	bluePaddle.setOutlineColor(sf::Color::Black);
	bluePaddle.setFillColor(sf::Color(50, 50, 255));
	bluePaddle.setOrigin({ paddleSize.x / 2, paddleSize.y / 2 });

	// Create the Ball
	sf::CircleShape ball;
	ball.setRadius(ballRadius - 4); // Removing to account for outline
	ball.setOutlineThickness(4);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin({ ballRadius / 2, ballRadius / 2 }); // Setting Origin to center of the ball
	
	// Load Font
	sf::Font arial("fonts/Arial.ttf"); // Arial is a placeholder, Want something more Pixelated to fit theme

	// Title Text -> Need to Change as it looks ugly...but it works for now. (Might ask friend for a "Logo"/Splash-art of a pong thing)
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

	// Sound
	sf::SoundBuffer pbuffer("sounds/paddle_bounce.wav");
	sf::Sound paddleBounce(pbuffer);
	sf::SoundBuffer wbuffer("sounds/wall_bounce.wav");
	sf::Sound wallBounce(wbuffer);
	sf::SoundBuffer sbuffer("sounds/score_point.wav");
	sf::Sound scorePoint(sbuffer);
	sf::Music backgroundMusic("sounds/background_music.mp3");

	paddleBounce.setVolume(10);
	wallBounce.setVolume(10);
	backgroundMusic.setVolume(5);

	backgroundMusic.setLooping(true);
	backgroundMusic.play();

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
					moveDelay.restart();
				}
			}
		}

		if (moveDelay.getElapsedTime() > sf::seconds(1))
		{
			moveBall = true; // Allow ball movement
			moveDelay.stop(); // Stop the Delay clock as we dont need to count up anymore so no reason not to stop it
		}

		window.clear(sf::Color(50, 50, 50));
		const float deltaTime = clock.restart().asSeconds();

		if (isPlaying)
		{
			if (leftScore == 5 || rightScore == 5)
			{
				isPlaying = false;
				ballAngle = sf::degrees(0);

				std::string wl = (leftScore == 5) ? "You Win!" : "You Lose!";
				titleText.setString("    Pong!\n\n" + wl);

				leftScore = 0;
				rightScore = 0;
				leftScoreText.setString("0");
				rightScoreText.setString("0");
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && (redPaddle.getPosition().y - (paddleSize.y / 2)) > 10.0f)
			{
				redPaddle.move({ 0.0f, -paddleSpeed * deltaTime }); // Move ONLY on the Y Axis. Using negative speed gives us a negative number which will the be taken away from the Y value which moves us up 
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && (redPaddle.getPosition().y + (paddleSize.y / 2)) < HEIGHT - 5.0f)
			{
				redPaddle.move({ 0.0f, paddleSpeed * deltaTime }); // Using normal speed gives u a positive number will will add to the Y value
			}
			
			// AI Calculations
			// What needs to happen. Check if Time has reached a certain point (Elapsed time) if so if ball position is GREATER than paddle pos. We move Up! If Less than. We move down!
			// Bounds:
			// Up:   (bluePaddle.getPosition().y - (paddleSize.y / 2) > 5.0f)
			// Down: (bluePaddle.getPosition().y + (paddleSize.y / 2) < HEIGHT - 5.0f)
			// Tried -> Limiting movement to only when it is coming towards AI Side with (&& (ballAngle.asDegrees() > -90 && ballAngle.asDegrees() < 90))
			// Looked too FAST!
			// Movement -> Movement Boundary = 10.0f -> 795.0f (As Height is 800)
			if ((bluePaddle.getPosition().y - (paddleSize.y / 2) > 10.0f) && 
				(bluePaddle.getPosition().y + (paddleSize.y / 2) < HEIGHT - 5.0f))
			{
				bluePaddle.move({ 0.0f, computerPaddleSpeed * deltaTime });

				// Ensuring the Paddle doesnt get stuck after movement by moving it 0.1f from the boundary
				if (bluePaddle.getPosition().y - (paddleSize.y / 2) < 10.0f)
					bluePaddle.setPosition({ (WIDTH - 30.0f), ((paddleSize.y / 2) + 10.1f) });
				else if (bluePaddle.getPosition().y + (paddleSize.y / 2) > HEIGHT - 5.0f)
					bluePaddle.setPosition({ (WIDTH - 30.0f), (HEIGHT - (paddleSize.y / 2) - 5.1f) });
			}

			// Every 1ms make computer able to "Change his mind" with the paddle direction while giving me the option to change it in code.
			if (computerClock.getElapsedTime() > computerTime)
			{
				computerClock.restart(); // Restart clock to 0ms

				// This calculation is important as we want to move at the proper speed which is not possible if movement logic is in this statement
				if (ball.getPosition().y + ballRadius > bluePaddle.getPosition().y + (paddleSize.y / 2))
					computerPaddleSpeed = paddleSpeed;
				else if (ball.getPosition().y - ballRadius < bluePaddle.getPosition().y - (paddleSize.y / 2))
					computerPaddleSpeed = -paddleSpeed;
				else
					computerPaddleSpeed = 0.0f;
			}
			
			if (moveBall)
			{
				// Move Ball by the value of Speed * Time for x value and the angle as the Y value
				ball.move({ ballSpeed * deltaTime, ballAngle });
			}

			// Scoring
			if (ball.getPosition().x - ballRadius < 0)
			{
				rightScoreText.setString(std::to_string(++rightScore));
				scorePoint.play();
				
				// Stop Ball from Moving
				moveBall = false;
				moveDelay.restart();

				ball.setPosition({ WIDTH / 2, HEIGHT / 2 });

				// Random Angle
				std::uniform_real_distribution<float> dist(135, 225);
				ballAngle = sf::degrees(fmod(dist(rng) + 180.0f, 360.0f) - 180.0f);
			}
			if (ball.getPosition().x + ballRadius >= WIDTH)
			{
				leftScoreText.setString(std::to_string(++leftScore));
				scorePoint.play();

				// Stop Ball from Moving
				moveBall = false;
				moveDelay.restart();

				ball.setPosition({ WIDTH / 2, HEIGHT / 2 });

				std::uniform_real_distribution<float> dist(-45, 45);
				ballAngle = sf::degrees(fmod(dist(rng) + 180.0f, 360.0f) - 180.0f);
			}

			// Collision Check for Paddles, Top Wall and Bottom Wall
			std::uniform_real_distribution<float> dist(0, 20);
			// Left Paddle
			if (ball.getPosition().x - ballRadius < redPaddle.getPosition().x + paddleSize.x / 2  && ball.getPosition().x - ballRadius > redPaddle.getPosition().x &&
				ball.getPosition().y + ballRadius >= redPaddle.getPosition().y - paddleSize.y / 2 && ball.getPosition().y - ballRadius <= redPaddle.getPosition().y + paddleSize.y / 2)
			{
				// These conditions will either give a slight upward angle or slight downward angle depending on whether the ball hit top or bottom of the paddle
				if (ball.getPosition().y > redPaddle.getPosition().y)
					ballAngle = sf::degrees(180) - ballAngle + sf::degrees(dist(rng));
				else
					ballAngle = sf::degrees(180) - ballAngle - sf::degrees(dist(rng));
				paddleBounce.play();
				ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.0f, 360.0f) - 180.0f);
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
				paddleBounce.play();
				ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.0f, 360.0f) - 180.0f);
				ball.setPosition({ bluePaddle.getPosition().x - ballRadius - paddleSize.x / 2 - 0.1f, ball.getPosition().y });
			}
			// Top Wall
			if (ball.getPosition().y - ballRadius < 0)
			{
				wallBounce.play();
				// Simply Invert the Balls Angle to flip the Y direction
				ballAngle = -ballAngle;
				ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.0f, 360.0f) - 180.0f);
				ball.setPosition({ ball.getPosition().x, ball.getPosition().y + ballRadius + 0.1f });
			}
			// Bottom Wall
			if (ball.getPosition().y + ballRadius > HEIGHT)
			{
				wallBounce.play();
				// Simply Invert the Balls Angle to flip the Y direction
				ballAngle = -ballAngle;
				ballAngle = sf::degrees(fmod(ballAngle.asDegrees() + 180.0f, 360.0f) - 180.0f);
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