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

	//�\�[�g�p
	bool operator<(const Paddle& rhs) const
	{
		return m_sort_y < rhs.m_sort_y;
	}
	void Set_sort_y() {
		m_sort_y = _center.Get_y();
	}

private:
	bool m_materialization;//�v���C���[�ɓ��܂�Ď��̉��������ǂ���
	int m_flyingAngle;//��Ԋp�x(���܂��܂�)

	float m_paddleSpeed;//����̉����̑��x

	float m_sort_y;//�\�[�g�p

	unsigned int m_color{};
};
