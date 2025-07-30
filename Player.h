#pragma once
#include "BoxCollider.h"

class Player : public BoxCollider
{
public:
	Player(Vector2 pos, Vector2 size);
	~Player();

	Player(const Player& p) = delete;
	Player& operator=(const Player& p) = delete;

    void Update();
	void Draw() const;

	bool Get_canJump() const {
		return canJump;
	}
	void CanJump() {
		canJump = true;
	}

	float vel_y; // y方向の速度

private:
	int handle;
	bool canJump;//ジャンプ出来るかどうか

	float jumpInputTime;//ジャンプ入力がされた時間
};

