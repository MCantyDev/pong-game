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
	static int GetScore(PaddleSide side);
	static PaddleSide GetWinner();

private:
	ScoreManager() = default;
	static ScoreManager* instance;

	static const int WINNING_SCORE = 5;

	static int leftScore;
	static int rightScore;

	static int leftTotalWins;
	static int rightTotalWins;
};

#endif // SCOREMANAGER_H