#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

// Drawables
#include "drawables/Paddle.h"

// Observer
#include "Observer/Observer.h"


class ScoreManager : public Observer<PaddleSide>
{
public:
	static ScoreManager* GetInstance();
	~ScoreManager() = default;

	void update(PaddleSide scorer) override;

	// Game Ending and Scores
	bool checkGameEnd();
	static void ResetScores();
	static void ResetTotalWins();

private:
	ScoreManager() = default;
	static ScoreManager* instance;

	const int WINNING_SCORE = 3;

	static int leftScore;
	static int rightScore;

	static int leftTotalWins;
	static int rightTotalWins;
};

#endif // SCOREMANAGER_H