#include "Player.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRateManager.h"
#include "InputManager.h"

Player::Player(Vector2 pos, Vector2 size) : BoxCollider(pos, size)
{
	handle = LoadGraph("画像/300-300.png");

	canJump = false;

	vel_y = 0;

	jumpInputTime = 0;
}
Player::~Player() 
{
	DeleteGraph(handle);
}

void Player::Update()
{

	movementPerFrame = {0, 0};
	isCollisionResponse = false;

	//重力
	vel_y += GravityAcceleration * FrameRateManager::getInstance()->Get_Deltatime();
	//ジャンプ
	if (InputManager::getInstance()->key_down[KEY_INPUT_SPACE] && canJump) {
		canJump = false;
		vel_y = -1.0f * PlayerJumpPower;
		jumpInputTime = GetNowHiPerformanceCount() / 1000000.0f;
	}
	if (!canJump) {
		//ジャンプボタンが離されたら
		if (InputManager::getInstance()->key_up[KEY_INPUT_SPACE]) {
			if ((GetNowHiPerformanceCount() / 1000000.0f) - jumpInputTime < 0.1f) vel_y += 0.2f;
		}
	}
	movementPerFrame.y = vel_y;
}

void Player::Draw() const
{
	DrawExtendGraph((int)fourSides.leftSide, (int)fourSides.topSide, (int)fourSides.rightSide, (int)fourSides.bottomSide, handle, TRUE);
}