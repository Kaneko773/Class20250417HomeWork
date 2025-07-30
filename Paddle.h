#pragma once
#include "BoxCollider.h"

class Paddle : public BoxCollider
{
public:
	Paddle(Vector2 pos, Vector2 size);
	~Paddle();

	void SteppedOn() {
		materialization = true;
	}
	bool Get_m_materialization() const{
		return materialization;
	}

	void Update(float fallSpeed);
	bool RangeJudge() const;
	void Draw() const;

	//ソート用
	bool operator<(const Paddle& rhs) const//y座標を比べるので昇順のまま
	{
		return sort_y < rhs.sort_y;
	}
	void Set_sort_y() {
		sort_y = center.y;
	}

private:
	bool materialization;//プレイヤーに踏まれて実体化したかどうか
	int flyingAngle;//飛ぶ角度(踏まれるまで)

	float paddleSpeed;//非実体化時の速度

	float sort_y;//ソート用

	unsigned int color;//パドルの色
};
