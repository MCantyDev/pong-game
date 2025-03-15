#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "state/State.h"

// SMFL Includes
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

/*
* @class MenuState
* @brief Menu State of the Game - Signifies the User is at the Main Menu of the Game
* 
* Menu State will give user access to playing state and settings state
*/
class MenuState : public State
{
public:
	MenuState();
	~MenuState() = default;

	virtual void handleInput() override;
	virtual void update() override;
	virtual void render() override;

private:
	void initialiseText();

	sf::RenderWindow& window;

	sf::Font arial;

	sf::Text titleText = sf::Text(arial, "Pong!", 50);
	sf::Text instructionText = sf::Text(arial, "Press Enter to Play");
};

#endif // MENUSTATE_H