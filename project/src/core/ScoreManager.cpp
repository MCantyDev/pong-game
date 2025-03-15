#include "core/ScoreManager.h"

ScoreManager* ScoreManager::instance = nullptr;

// Score Variables
int ScoreManager::leftScore = 0;
int ScoreManager::leftTotalWins = 0;

int ScoreManager::rightScore = 0;
int ScoreManager::rightTotalWins = 0;

ScoreManager* ScoreManager::GetInstance()
{
	if (!instance)
		instance = new ScoreManager();

	return instance;
}

void ScoreManager::update(PaddleSide scorer)
{
	if (scorer == PaddleSide::LEFT)
		leftScore++;
	else if (scorer == PaddleSide::RIGHT)
		rightScore++;
}

bool ScoreManager::checkGameEnd()
{
	if (leftScore == WINNING_SCORE)
	{
		leftTotalWins++;
		return true;
	}
	else if (rightScore == WINNING_SCORE)
	{
		rightTotalWins++;
		return true;
	}
	return false;
}

int ScoreManager::GetScore(PaddleSide side)
{
	if (side == PaddleSide::LEFT)
		return leftScore;

	return rightScore;
}

void ScoreManager::ResetScores()
{
	leftScore = 0;
	rightScore = 0;
}

void ScoreManager::ResetTotalWins()
{
	leftTotalWins = 0;
	rightTotalWins = 0;
}