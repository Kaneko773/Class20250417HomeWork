#include "Paddle.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRate.h"
#include "math.h"

Paddle::Paddle(Vector2<float> pos, Vector2<float> size) {
	_center = pos;
	_size = size;
	
	m_materialization = false;

	if (pos.Get_x() < 0) {
		//1�`10
		flyingAngle = rand() % 10 + 1;
	}
	else {
		//170�`179
		flyingAngle = rand() % 10 + 170;
	}

	paddleSpeed = PaddleSpeed;//�����ő�������
	vel = InitialVelocity;
}
Paddle::~Paddle() {

}

void Paddle::Update() {
	_movementPerFrame.Reset();
	_isCollisionResponse = false;

	if (m_materialization) {
		_movementPerFrame.Set_y(_movementPerFrame.Get_y() + vel * FrameRate::Get_Deltatime());
		vel += PaddleAcceleration * FrameRate::Get_Deltatime();
	}
	else {
		//�w��̕����ɔ��ł���
		double angle = 3.14159 / (static_cast<double>(180) / flyingAngle);
		_movementPerFrame.Set_x(_movementPerFrame.Get_x() + PaddleSpeed * FrameRate::Get_Deltatime() * (float)cos(angle));
		_movementPerFrame.Set_y(_movementPerFrame.Get_y() + PaddleSpeed * FrameRate::Get_Deltatime() * (float)sin(angle));
	}
}

bool Paddle::RangeJudge() {
	//�����͈͂��o�Ă�����false��Ԃ�
	if (Get_topSide() > ScreenHeight
		|| Get_leftSide() > ScreenWidth + PaddleSizeWidth
		|| Get_rightSide() < 0 - PaddleSizeWidth)
	{
		return false;
	}

	return true;
}

void Paddle::Draw() {
	DrawBox((int)Get_leftSide(), (int)Get_topSide(), (int)Get_rightSide(), (int)Get_bottomSide(), GetColor(255, 255, 255), m_materialization ? TRUE : FALSE);
}