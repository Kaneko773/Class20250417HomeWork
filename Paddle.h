#pragma once
#include "Vector2.h"
#include "BoxCollider.h"

class Paddle
{
public:
	Paddle(float x, float y, int width, int height, int arrayNum);
	virtual ~Paddle();

	BoxCollider Get_m_boxCollider() const {
		return m_boxCollider;
	}
	BoxCollider* Test_Get_mboxCollider() {
		return &m_boxCollider;
	}//
	int Get_m_arrayNum() const {
		return m_arrayNum;
	}
	void Set_m_arrayNum(int num) {
		m_arrayNum = num;
	}
	void SteppedOn() {
		m_materialization = true;
	}

	bool Update();
	void Draw();

	//�g���H
	Paddle(const Paddle& p) {
		m_boxCollider = p.m_boxCollider;
		m_materialization = p.m_materialization;
		m_arrayNum = p.m_arrayNum;
		flyingAngle = p.flyingAngle;
	}
	Paddle& operator=(const Paddle& p) {
		if (this == &p) return *this;
		m_boxCollider = p.m_boxCollider;
		m_materialization = p.m_materialization;
		m_arrayNum = p.m_arrayNum;
		flyingAngle = p.flyingAngle;
		return *this;
	}

private:
	BoxCollider m_boxCollider;
	bool m_materialization;//�v���C���[�ɓ��܂�Ď��̉��������ǂ���
	int m_arrayNum;//�z��̓Y����

	int flyingAngle;//��Ԋp�x(���܂��܂�)
};
