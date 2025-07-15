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

	//ソート用
	bool operator<(const Paddle& rhs) const
	{
		return sort_y < rhs.sort_y;
	}
	void Set_sort_y() {
		sort_y = _center.Get_y();
	}

private:
	bool m_materialization;//プレイヤーに踏まれて実体化したかどうか
	int flyingAngle;//飛ぶ角度(踏まれるまで)

	float paddleSpeed;//非実体化時の速度
	float vel;//実体化時の速度

	float sort_y;//ソート用
};
