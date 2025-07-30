#include "ScoreManager.h"

ScoreManager* ScoreManager::pInstance = nullptr;
ScoreManager::ScoreManager()
{
	highScore = 0;
	prevGameScore = 0;
}
ScoreManager* ScoreManager::getInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new ScoreManager();
	}
	return pInstance;
}

void ScoreManager::create()
{
	if (pInstance == nullptr)
	{
		pInstance = new ScoreManager();
	}
}

void ScoreManager::destroy()
{
	if (pInstance != nullptr)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}

void ScoreManager::Set_prevGameScore(int score) {
	prevGameScore = score;
	if (prevGameScore > highScore) {
		highScore = prevGameScore;
	}
}