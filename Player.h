#pragma once
#include "Vector2.h"
#include "BoxCollider.h"

class Player
{
public:
	Player(float x, float y);
	virtual ~Player();

	BoxCollider Get_m_boxCollider() {
		return m_boxCollider;
	}

	void Update();
	void Draw();

private:
	int _gHandle;
	BoxCollider m_boxCollider;
};

