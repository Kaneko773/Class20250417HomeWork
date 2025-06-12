#pragma once
#include "Vector2.h"
#include "BoxCollider.h"

class Player
{
public:
	Player(float x, float y);
	virtual ~Player();

	BoxCollider Get_m_boxCollider() const {
		return m_boxCollider;
	}
	BoxCollider* Test_Get_mboxCollider() {
		return &m_boxCollider;
	}//

	//�g���H
	Player(const Player& p) {
		_gHandle = p._gHandle;
		m_boxCollider = p.m_boxCollider;
		canJump = p.canJump;
	}
	Player& operator=(const Player& p) {
		if (this == &p) return *this;
		_gHandle = p._gHandle;
		m_boxCollider = p.m_boxCollider;
		canJump = p.canJump;
		return *this;
	}

	float Get_amountOfMovement();

	bool Update();
	void Draw();

private:
	int _gHandle;
	BoxCollider m_boxCollider;
	bool canJump;//�W�����v�o���邩�ǂ���
};

