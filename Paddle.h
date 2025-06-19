#pragma once
#include "BoxCollider.h"

class Paddle : public BoxCollider
{
public:
	Paddle(float x, float y, int width, int height);
	virtual ~Paddle();

	void SteppedOn() {
		m_materialization = true;
	}

	bool Update();
	void Draw();

private:
	bool m_materialization;//プレイヤーに踏まれて実体化したかどうか
	int flyingAngle;//飛ぶ角度(踏まれるまで)
};
