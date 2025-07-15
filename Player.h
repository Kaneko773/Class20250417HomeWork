#pragma once
#include "BoxCollider.h"

class Player : public BoxCollider
{
public:
	Player(Vector2<float> pos);
	virtual ~Player();

	Player(const Player& p) = delete;
	Player& operator=(const Player& p) = delete;

    void Update();
	void Draw();

	bool Get_canJump() {
		return canJump;
	}
	void CanJump() {
		canJump = true;
	}

	float vel_y; // y方向の速度

private:
	int _gHandle;
	bool canJump;//ジャンプ出来るかどうか
};

