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
		//1`10
		m_flyingAngle = rand() % 10 + 1;
	}
	else {
		//170`179
		m_flyingAngle = rand() % 10 + 170;
	}

	m_paddleSpeed = PaddleSpeed_LowestValue * (1.0f + (0.1f * (rand() % 10 + 1)));//—”‚Å‘‚­‚·‚é

	m_sort_y = _center.Get_y();

	switch (rand() % 3)
	{
	case 0:
		m_color = GetColor(255, rand() % 256, rand() % 256);
		break;
	case 1:
		m_color = GetColor(rand() % 256, 255, rand() % 256);
		break;
	case 2:
		m_color = GetColor(rand() % 256, rand() % 256, 255);
		break;
	}
}
Paddle::~Paddle() {

}

void Paddle::Update(float fallSpeed) {
	_movementPerFrame.Reset();
	_isCollisionResponse = false;

	if (m_materialization) {
		_movementPerFrame.Set_y(_movementPerFrame.Get_y() + fallSpeed * FrameRate::Get_Deltatime());
	}
	else {
		//Žw’è‚Ì•ûŒü‚É”ò‚ñ‚Å‚¢‚­
		double angle = 3.14159 / (static_cast<double>(180) / m_flyingAngle);
		_movementPerFrame.Set_x(_movementPerFrame.Get_x() + m_paddleSpeed * FrameRate::Get_Deltatime() * (float)cos(angle));
		_movementPerFrame.Set_y(_movementPerFrame.Get_y() + m_paddleSpeed * FrameRate::Get_Deltatime() * (float)sin(angle));
	}
}

bool Paddle::RangeJudge() {
	//‚à‚µ”ÍˆÍ‚ðo‚Ä‚¢‚½‚çfalse‚ð•Ô‚·
	if (Get_topSide() > ScreenHeight
		|| Get_leftSide() > ScreenWidth + PaddleSizeWidth
		|| Get_rightSide() < 0 - PaddleSizeWidth)
	{
		return false;
	}

	return true;
}

void Paddle::Draw() {
	DrawBox((int)Get_leftSide(), (int)Get_topSide(), (int)Get_rightSide(), (int)Get_bottomSide(), m_color, m_materialization ? TRUE : FALSE);
}