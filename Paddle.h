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

	//�\�[�g�p
	bool operator<(const Paddle& rhs) const//y���W���ׂ�̂ŏ����̂܂�
	{
		return sort_y < rhs.sort_y;
	}
	void Set_sort_y() {
		sort_y = center.y;
	}

private:
	bool materialization;//�v���C���[�ɓ��܂�Ď��̉��������ǂ���
	int flyingAngle;//��Ԋp�x(���܂��܂�)

	float paddleSpeed;//����̉����̑��x

	float sort_y;//�\�[�g�p

	unsigned int color;//�p�h���̐F
};
