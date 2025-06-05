#include "Paddle.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRate.h"
#include "math.h"

Paddle::Paddle(float x, float y, int width, int height, int arrayNum) {

	Vector2<float> size;
	size.Get_height() = height;
	size.Get_width() = width;

	Vector2<float> center;
	center.Get_x() = x;
	center.Get_y() = y;

	m_boxCollider.Initialization(center, size);
	
	m_materialization = false;

	m_arrayNum = arrayNum;

	if (center.Get_x() < 0) {
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

bool Paddle::Update() {
	BoxCollider tempCollider = m_boxCollider;

	//もし範囲を出ていたらfalseを返す
	if (tempCollider.Get_topSide() > ScreenHeight
		|| tempCollider.Get_leftSide() > ScreenWidth + PaddleSizeWidth
		|| tempCollider.Get_rightSide() < 0 - PaddleSizeWidth) 
	{
		return false;
	}

	if (m_materialization) {
		//１秒間に50ドット落ちる
		tempCollider._center.Get_y() += 50.0f * FrameRate::Get_Deltatime();
	}
	else {
		//指定の方向に飛んでいく(テスト：1秒間に100ドット進む)
		double angle = 3.14159 / (static_cast<double>(180) / flyingAngle);
		tempCollider._center.Get_x() += 100.0f * FrameRate::Get_Deltatime() * cos(angle);
		tempCollider._center.Get_y() += 100.0f * FrameRate::Get_Deltatime() * sin(angle);
	}

	m_boxCollider._center = tempCollider._center;

	return true;
}

void Paddle::Draw() {
	DrawBox(m_boxCollider.Get_leftSide(), m_boxCollider.Get_topSide(), m_boxCollider.Get_rightSide(), m_boxCollider.Get_bottomSide(), GetColor(255, 255, 255), m_materialization ? TRUE : FALSE);
}