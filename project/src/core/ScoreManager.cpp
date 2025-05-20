#include "core/ScoreManager.h"

ScoreManager *ScoreManager::instance = nullptr;

// Score Variables
int ScoreManager::leftScore = 0;
int ScoreManager::leftTotalWins = 0;

int ScoreManager::rightScore = 0;
int ScoreManager::rightTotalWins = 0;

const int ScoreManager::WINNING_SCORE;

ScoreManager::~ScoreManager()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

ScoreManager *ScoreManager::GetInstance()
{
	if (!instance)
		instance = new ScoreManager();

	return instance;
}

void ScoreManager::DeleteInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
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

PaddleSide ScoreManager::GetWinner()
{
	if (leftScore == WINNING_SCORE)
		return PaddleSide::LEFT;

	return PaddleSide::RIGHT;
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