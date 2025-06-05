#pragma once
#include "Vector2.h"
#include "BoxCollider.h"

class Paddle
{
public:
	Paddle(float x, float y, int width, int height, int arrayNum);
	virtual ~Paddle();

	int Get_m_arrayNum() {
		return m_arrayNum;
	}
	void Set_m_arrayNum(int num) {
		m_arrayNum = num;
	}

	bool Update();
	void Draw();

private:
	BoxCollider m_boxCollider;
	bool m_materialization;//プレイヤーに踏まれて物体化したかどうか
	int m_arrayNum;//配列の添え字

	int flyingAngle;//飛ぶ角度(踏まれるまで)
};
