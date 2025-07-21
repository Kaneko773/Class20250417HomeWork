#pragma once

class ScoreManager
{
public:
	ScoreManager() {
		_highScore = 0;
		_prevGameScore = 0;
	}

	int Get_highScore() const {
		return _highScore;
	}
	int Get_prevGameScore() const {
		return _prevGameScore;
	}
	void Set_prevGameScore(int score) {
		_prevGameScore = score;
		if (_prevGameScore > _highScore) {
			_highScore = _prevGameScore;
		}
	}

private:
	int _highScore;
	int _prevGameScore;
};

