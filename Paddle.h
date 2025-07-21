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

	void Update(float fallSpeed);
	bool RangeJudge();
	void Draw();

	//ソート用
	bool operator<(const Paddle& rhs) const
	{
		return m_sort_y < rhs.m_sort_y;
	}
	void Set_sort_y() {
		m_sort_y = _center.Get_y();
	}

private:
	bool m_materialization;//プレイヤーに踏まれて実体化したかどうか
	int m_flyingAngle;//飛ぶ角度(踏まれるまで)

	float m_paddleSpeed;//非実体化時の速度

	float m_sort_y;//ソート用

	unsigned int m_color{};
};
