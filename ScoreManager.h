#pragma once

class ScoreManager
{
public:
	int Get_highScore() const {
		return highScore;
	}
	int Get_prevGameScore() const {
		return prevGameScore;
	}
	void Set_prevGameScore(int score);

	ScoreManager(const ScoreManager&) = delete;
	void operator=(const ScoreManager&) = delete;

private:
	ScoreManager();
	virtual ~ScoreManager() {};

private:
	static ScoreManager* pInstance;

	int highScore;
	int prevGameScore;

public:
	static ScoreManager* getInstance();
	static void create();
	static void destroy();
};

