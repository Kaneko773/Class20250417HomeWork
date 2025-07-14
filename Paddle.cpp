#include "Paddle.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRate.h"
#include "math.h"

Paddle::Paddle(Vector2<float> pos, Vector2<float> size/*float x, float y, int width, int height*/) {

	//Vector2<float> size((float)width, (float)height);
	//Vector2<float> center(x, y);

	//_center = center;
	//_size = size;

	_center = pos;
	_size = size;
	
	m_materialization = false;

	if (pos.Get_x() < 0) {
		//1～25
		flyingAngle = rand() % 25 + 1;
	}
	else {
		//155～179
		flyingAngle = rand() % 25 + 155;
	}
}
Paddle::~Paddle() {

}

void Paddle::Update() {
	_movementPerFrame.Reset();
	_isCollisionResponse = false;

	if (m_materialization) {
		//１秒間に50ドット落ちる
		//_movementPerFrame.Get_y() += 50.0f * FrameRate::Get_Deltatime();
		_movementPerFrame.Set_y(_movementPerFrame.Get_y() + 50.0f * FrameRate::Get_Deltatime());
	}
	else {
		//指定の方向に飛んでいく(テスト：1秒間に100ドット進む)
		double angle = 3.14159 / (static_cast<double>(180) / flyingAngle);
		//_movementPerFrame.Get_x() += 100.0f * FrameRate::Get_Deltatime() * (float)cos(angle);
		//_movementPerFrame.Get_y() += 100.0f * FrameRate::Get_Deltatime() * (float)sin(angle);
		_movementPerFrame.Set_x(_movementPerFrame.Get_x() + 100.0f * FrameRate::Get_Deltatime() * (float)cos(angle));
		_movementPerFrame.Set_y(_movementPerFrame.Get_y() + 100.0f * FrameRate::Get_Deltatime() * (float)sin(angle));
	}
}

bool Paddle::RangeJudge() {
	//もし範囲を出ていたらfalseを返す
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