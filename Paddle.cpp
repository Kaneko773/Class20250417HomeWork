#include "Paddle.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRate.h"
#include "math.h"

Paddle::Paddle(float x, float y, int width, int height) {

	Vector2<float> size((float)width, (float)height);
	Vector2<float> center(x, y);

	_center = center;
	_size = size;
	
	m_materialization = false;

	if (center.Get_x() < 0) {
		//1�`25
		flyingAngle = rand() % 25 + 1;
	}
	else {
		//155�`179
		flyingAngle = rand() % 25 + 155;
	}
}
Paddle::~Paddle() {

}

bool Paddle::Update() {
	BoxCollider temp_collider;
	temp_collider._center = _center;
	temp_collider._size = _size;

	//�����͈͂��o�Ă�����false��Ԃ�
	if (Get_topSide() > ScreenHeight
		|| Get_leftSide() > ScreenWidth + PaddleSizeWidth
		|| Get_rightSide() < 0 - PaddleSizeWidth) 
	{
		return false;
	}

	if (m_materialization) {
		//�P�b�Ԃ�50�h�b�g������
		temp_collider._center.Get_y() += 50.0f * FrameRate::Get_Deltatime();
	}
	else {
		//�w��̕����ɔ��ł���(�e�X�g�F1�b�Ԃ�100�h�b�g�i��)
		double angle = 3.14159 / (static_cast<double>(180) / flyingAngle);
		temp_collider._center.Get_x() += 100.0f * FrameRate::Get_Deltatime() * (float)cos(angle);
		temp_collider._center.Get_y() += 100.0f * FrameRate::Get_Deltatime() * (float)sin(angle);
	}

	_center = temp_collider._center;

	return true;
}

void Paddle::Draw() {
	DrawBox((int)Get_leftSide(), (int)Get_topSide(), (int)Get_rightSide(), (int)Get_bottomSide(), GetColor(255, 255, 255), m_materialization ? TRUE : FALSE);
}