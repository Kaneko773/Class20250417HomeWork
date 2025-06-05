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
	bool m_materialization;//�v���C���[�ɓ��܂�ĕ��̉��������ǂ���
	int m_arrayNum;//�z��̓Y����

	int flyingAngle;//��Ԋp�x(���܂��܂�)
};
