#pragma once
#include "BoxCollider.h"

class Player : public BoxCollider
{
public:
	Player(float x, float y);
	virtual ~Player();

#if 0
	BoxCollider Get_m_boxCollider() const {
		return m_boxCollider;
	}
	BoxCollider* Test_Get_mboxCollider() {
		return &m_boxCollider;
	}//
#endif

	Player(const Player& p) = delete;
	Player& operator=(const Player& p) = delete;

	float Get_amountOfMovement();

	bool Update();
	void Draw();

	bool Get_canJump() {
		return canJump;
	}

private:
	int _gHandle;
	//BoxCollider m_boxCollider;
	bool canJump;//ƒWƒƒƒ“ƒvo—ˆ‚é‚©‚Ç‚¤‚©
};

