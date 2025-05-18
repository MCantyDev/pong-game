#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "state/State.h"

// GameEnums Include
#include "GameEnums.h"

// SFML Includes
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

// Utility Includes
#include "factory/ButtonFactory.h"

// Standard Library Includes
#include <vector>

/*
* @class GameOverState
* @brief Game Over State of the Game - Signifies the game has ended
*
* Game Over State allows user to return to Play Again, Return to Main Menu, or Exit Application
*/
class GameOverState : public State
{
public:
	GameOverState(PaddleSide winner, GameMode mode);
	~GameOverState() = default;

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
	// Private Functions
	void initialiseText(PaddleSide winner, GameMode mode);
	void initialiseButtons();

	// Button Click Functions
	void mainMenu();
	void playAgain();
	void closeWindow();

	// Private Variables
	PaddleSide winner;
	GameMode mode;

	// Text
	sf::Font font;
	sf::Text scoreText = sf::Text(font, "", 50); // Initialise with Empty String - Will be set to Winner
	sf::Text winnerText = sf::Text(font, "", 30); // Initialise with Empty String - Will be set to Score

	// Buttons
	std::vector<std::unique_ptr<Button>> buttons;
};

#endif // GAMEOVERSTATE_H