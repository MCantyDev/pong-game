#ifndef DELTATIMECLOCK_H
#define DELTATIMECLOCK_H

// SFML Include
#include "SFML/System.hpp"

/**
 * @class DeltaTimeClock
 * @brief Singleton class to track the time elapsed between frames (delta time).
 *
 * Used for frame rate independent movement and timing within the Pong game.
 */
class DeltaTimeClock
{
public:
	/**
	 * @brief Destructor to clean up the DeltaTimeClock.
	 */
	~DeltaTimeClock();

	/**
	 * @brief Returns the singleton instance of the DeltaTimeClock.
	 * @return Pointer to the single DeltaTimeClock instance.
	 */
	static DeltaTimeClock *GetInstance();

	/**
	 * @brief Deletes the singleton instance, freeing allocated resources.
	 */
	static void DeleteInstance();

	/**
	 * @brief Retrieves the current delta time value.
	 *
	 * Delta time represents the time elapsed since the last frame update,
	 * useful for consistent game logic updates.
	 * @return Delta time as a float (seconds).
	 */
	static float GetDeltaTime();

	/**
	 * @brief Updates the delta time by measuring elapsed time since last update.
	 *
	 * Should be called once per frame to keep delta time current.
	 */
	void update();

private:
	DeltaTimeClock();
	static DeltaTimeClock *instance;

	// Deleted copy constructors to prevent copying of the singleton.
	DeltaTimeClock(const DeltaTimeClock &) = delete;
	DeltaTimeClock &operator=(const DeltaTimeClock &) = delete;

	sf::Clock deltaClock;
	static float deltaTime;
};

#endif // DELTATIMECLOCK_H