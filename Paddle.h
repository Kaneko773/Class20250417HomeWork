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

	const float Get_center_y() {//
		return _center.Get_y();
	}

	void Update();
	bool RangeJudge();
	void Draw();

	//�\�[�g�p
	bool operator<(const Paddle& rhs) const
	{
		return sort_y < rhs.sort_y;
	}
	void Set_sort_y() {
		sort_y = _center.Get_y();
	}

private:
	bool m_materialization;//�v���C���[�ɓ��܂�Ď��̉��������ǂ���
	int flyingAngle;//��Ԋp�x(���܂��܂�)

	float sort_y;//�\�[�g�p
};
