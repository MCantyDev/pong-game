#ifndef STATEMANAGER_H
#define STATEMANAGER_H

class State; // Forward Declare State to stop Circular dependency
class InputManager;

// SMFL Includes
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

// Standard Library Includes
#include <iostream>
#include <memory>

/**
 * @class StateManager
 * @brief Singleton class responsible for managing game states in the Pong game.
 *
 * The StateManager handles updating and rendering the current game state,
 * and manages state transitions using the State design pattern. It ensures
 * that only one state is active at a time and allows safe and debounced transitions.
 */
class StateManager
{
public:
    /**
     * @brief Destructor for StateManager.
     */
    ~StateManager();

    /**
     * @brief Retrieves the singleton instance of the StateManager.
     * @return Pointer to the StateManager instance.
     */
    static StateManager *GetInstance();

    /**
     * @brief Deletes the singleton instance of the StateManager.
     */
    static void DeleteInstance();

    /**
     * @brief Updates the current state.
     * Should be called once per frame to update game logic.
     */
    void update();

    /**
     * @brief Renders the current state.
     * Should be called once per frame to draw visuals to the screen.
     */
    void render();

    /**
     * @brief Sets a request to change the current state.
     * @param newState The new state to switch to.
     *
     * This does not change the state immediately—it sets a flag and stores
     * the new state to be applied during the next state check.
     */
    static void SetChangeState(std::unique_ptr<State> newState);

    /**
     * @brief Checks if a state change has been requested and applies it if allowed.
     * Includes debounce handling to prevent rapid state switching.
     */
    static void CheckStateChange();

    /**
     * @brief Gets the currently active state.
     * @return Pointer to the current State object.
     */
    static State *GetState();

private:
    StateManager();
    static StateManager *instance;

    static std::unique_ptr<State> state;
    static std::unique_ptr<State> nextState;
    static bool changeState;

    static sf::Clock swapClock;
    static bool canAction;
    static float debounceTime;
};

#endif // STATEMANAGER_H