#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

// Drawables
#include "drawables/Paddle.h"

// Observer
#include "Observer/Observer.h"

/**
 * @class ScoreManager
 * @brief Singleton class managing the scores in the Pong game.
 *
 * Implements the Observer pattern to update scores based on paddle events.
 * Tracks current scores, determines game end, and stores total wins.
 */
class ScoreManager : public Observer<PaddleSide>
{
public:
	/**
	 * @brief Destructor for ScoreManager.
	 */
	~ScoreManager();

	/**
	 * @brief Returns the singleton instance of the ScoreManager.
	 * @return Pointer to the ScoreManager instance.
	 */
	static ScoreManager *GetInstance();

	/**
	 * @brief Deletes the singleton instance, freeing allocated resources.
	 */
	static void DeleteInstance();

	/**
	 * @brief Updates scores when notified of a scoring event.
	 *
	 * @param scorer The paddle side (Left or Right) that scored.
	 */
	void update(PaddleSide scorer) override;

	/**
	 * @brief Checks whether the game has reached the winning score and ended.
	 * @return True if the game is over, false otherwise.
	 */
	bool checkGameEnd();

	/**
	 * @brief Resets the current game scores to zero for both sides.
	 */
	static void ResetScores();

	/**
	 * @brief Resets the total wins counters for both paddle sides.
	 *
	 * Note: Total wins are tracked but not currently displayed in the UI.
	 */
	static void ResetTotalWins();

	/**
	 * @brief Retrieves the current score for the specified paddle side.
	 * @param side The paddle side (Left or Right) to query.
	 * @return The current score of the given side.
	 */
	static int GetScore(PaddleSide side);

	/**
	 * @brief Determines and returns the winner paddle side if the game ended.
	 * @return The winning PaddleSide.
	 */
	static PaddleSide GetWinner();

private:
	ScoreManager() = default;

	static ScoreManager *instance;

	static const int WINNING_SCORE = 5;

	static int leftScore;
	static int rightScore;

	static int leftTotalWins;
	static int rightTotalWins;

	// Deleted copy constructors to prevent copying the singleton.
	ScoreManager(const ScoreManager &) = delete;
	ScoreManager &operator=(const ScoreManager &) = delete;
};

#endif // SCOREMANAGER_H