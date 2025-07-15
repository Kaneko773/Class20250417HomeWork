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

	float vel_y; // y�����̑��x

private:
	int _gHandle;
	bool canJump;//�W�����v�o���邩�ǂ���
};

