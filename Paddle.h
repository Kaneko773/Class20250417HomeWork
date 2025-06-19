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
	bool m_materialization;//�v���C���[�ɓ��܂�Ď��̉��������ǂ���
	int flyingAngle;//��Ԋp�x(���܂��܂�)
};
