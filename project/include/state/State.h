#ifndef STATE_H
#define STATE_H

#include "core/StateManager.h"

/**
 * @class State
 * @brief Abstract base class representing a game state.
 * 
 * All game states (e.g., MenuState, PlayingState, GameOverState)
 * inherit from this class and implement its interface. It defines the structure and
 * required functionality for each specific state, ensuring consistency across the game.
 * 
 * Each state must implement update and render logic, as well as command-handling methods
 * which are triggered via the InputManager using the Command Pattern.
 */
class State
{
public:
    State() = default;
    virtual ~State() = default;

    /**
     * @brief Update logic for the current state.
     */
    virtual void update() = 0;

    /**
     * @brief Render logic for the current state.
     */
    virtual void render() = 0;

    // Command-triggered actions (executed via Command pattern)
    /**
     * @brief Triggered when Player One moves up input key pressed.
     */
    virtual void PlayerOneMoveUp() = 0;

    /**
     * @brief Triggered when Player One moves down input key pressed.
     */
    virtual void PlayerOneMoveDown() = 0;

    /**
     * @brief Triggered when Player Two moves up input key pressed.
     */
    virtual void PlayerTwoMoveUp() = 0;

    /**
     * @brief Triggered when Player Two moves down input key pressed.
     */
    virtual void PlayerTwoMoveDown() = 0;

    /**
     * @brief Triggered to pause the game (Pause not yet Implemented).
     */
    virtual void Pause() = 0;

    /**
     * @brief Triggered to select an option (e.g., menu).
     */
    virtual void Select() = 0;

    /**
     * @brief Triggered to return or go back (e.g., from playing to menu).
     */
    virtual void Return() = 0;
};


#endif // STATE_H