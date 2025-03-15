#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "state/State.h"

// SMFL Includes
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

/*
* @class MenuState
* @brief Menu State of the Game - Signifies the User is at the Main Menu of the Game
* 
* Menu State will give user access to playing state and settings state
*/
class MainMenuState : public State
{
public:
	MainMenuState();
	~MainMenuState() = default;

	virtual void update() override;
	virtual void render() override;

	// Command Overrides
	virtual void PlayerOneMoveUp() override;
	virtual void PlayerOneMoveDown() override;
	virtual void PlayerTwoMoveUp() override;
	virtual void PlayerTwoMoveDown() override;
	virtual void Pause() override;
	virtual void Select() override;
	virtual void Return() override;

private:
	void initialiseText();
	void initialiseGraphics();

	sf::RenderWindow& window;

	sf::Font font;
	sf::Text titleText = sf::Text(font, "Pong!", 50);
	sf::Text instructionText = sf::Text(font, "Press Enter to Play");

	// Shapes for Paddle and Ball Graphics
	sf::RectangleShape leftPaddle;
	sf::RectangleShape rightPaddle;
	sf::CircleShape ball;
};

#endif // MAINMENUSTATE_H