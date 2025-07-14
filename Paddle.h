#pragma once
#include "BoxCollider.h"

class Paddle : public BoxCollider
{
public:
	Paddle(Vector2<float> pos, Vector2<float> size);
	virtual ~Paddle();

	void SteppedOn() {
		m_materialization = true;
	}
	bool Get_m_materialization() {
		return m_materialization;
	}

	void Update();
	bool RangeJudge();
	void Draw();

private:
	bool m_materialization;//プレイヤーに踏まれて実体化したかどうか
	int flyingAngle;//飛ぶ角度(踏まれるまで)
};
