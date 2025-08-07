#pragma once
#include "BoxCollider.h"

class Player_StateBase;

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

	float Get_jumpInputTime() const {
		return jumpInputTime;
	}
	void Set_jumpInputTime(float val) {
		jumpInputTime = val;
	}
	void Landing();

	void Set_vel_y(float val) {
		vel_y = val;
	}
	void Add_vel_y(float add) {
		vel_y += add;
	}

private:
	int handle;
	int handle_idle[10];
	int handle_jump;

	bool canJump;//ジャンプ出来るかどうか

	float jumpInputTime;//ジャンプ入力がされた時間

	float vel_y; // y方向の速度

	Player_StateBase* currentState;
};