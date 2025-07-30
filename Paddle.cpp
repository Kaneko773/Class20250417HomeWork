#include "Paddle.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRateManager.h"
#include "math.h"

Paddle::Paddle(Vector2 pos, Vector2 size) : BoxCollider(pos, size)
{
	materialization = false;

	if (pos.x < 0) {
		//1`10
		flyingAngle = rand() % 10 + 1;
	}
	else {
		//170`179
		flyingAngle = rand() % 10 + 170;
	}

	paddleSpeed = PaddleSpeed_LowestValue * (1.0f + (0.1f * (rand() % 10 + 1)));//—”‚Å‘‚­‚·‚é

	sort_y = center.y;

	color = 0;
	switch (rand() % 3)
	{
	case 0:
		color = GetColor(255, rand() % 256, rand() % 256);
		break;
	case 1:
		color = GetColor(rand() % 256, 255, rand() % 256);
		break;
	case 2:
		color = GetColor(rand() % 256, rand() % 256, 255);
		break;
	}
}
Paddle::~Paddle()
{

}

void Paddle::Update(float fallSpeed)
{
	movementPerFrame = {0, 0};
	isCollisionResponse = false;

	if (materialization) {
		movementPerFrame.y = fallSpeed * FrameRateManager::getInstance()->Get_Deltatime();
	}
	else {
		//Žw’è‚Ì•ûŒü‚É”ò‚ñ‚Å‚¢‚­
		double angle = 3.14159 / (static_cast<double>(180) / flyingAngle);
		movementPerFrame.x = paddleSpeed * FrameRateManager::getInstance()->Get_Deltatime() * (float)cos(angle);
		movementPerFrame.y = paddleSpeed * FrameRateManager::getInstance()->Get_Deltatime() * (float)sin(angle);
	}
}

bool Paddle::RangeJudge() const
{
	//‚à‚µ”ÍˆÍ‚ðo‚Ä‚¢‚½‚çfalse‚ð•Ô‚·
	if (fourSides.topSide > ScreenHeight
		|| fourSides.leftSide > ScreenWidth + PaddleSizeWidth
		|| fourSides.rightSide < 0 - PaddleSizeWidth)
	{
		return false;
	}

	return true;
}

void Paddle::Draw() const
{
	DrawBox((int)fourSides.leftSide, (int)fourSides.topSide, (int)fourSides.rightSide, (int)fourSides.bottomSide, color, materialization ? TRUE : FALSE);
}