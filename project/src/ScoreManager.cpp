#include "ScoreManager.h"

// State -> ScoreManager can only change Game State inside of Playing State
#include "state/MenuState.h"

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

	std::cout << "Score: " << leftScore << " : " << rightScore << std::endl;
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