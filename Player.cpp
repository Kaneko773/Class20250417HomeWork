#include "Player.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRate.h"
#include "InputManager.h"

Player::Player(Vector2<float> pos) {
	_gHandle = LoadGraph("画像/300-300.png");//使う画像
	//GetGraphSize(_gHandle, &PlayerPictureWidth, &PlayerPictureHeight);//画像サイズを取得

	Vector2<float> size(PlayerPictureWidth / ReductionMag, PlayerPictureHeight / ReductionMag);

	_center = pos;
	_size = size;

	canJump = false;

	vel_y = 0;

	jumpInputTime = 0;
}
Player::~Player() {
	DeleteGraph(_gHandle);
}

void Player::Update() {

	_movementPerFrame.Reset();
	_isCollisionResponse = false;

#if 0
	//左右移動
	if (CheckHitKey(KEY_INPUT_A) == 1) {//左
		_movementPerFrame.Set_x(_movementPerFrame.Get_x() - add * FrameRate::Get_Deltatime());
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {//右
		_movementPerFrame.Set_x(_movementPerFrame.Get_x() + add * FrameRate::Get_Deltatime());
	}
#endif

	//重力
	vel_y += GravityAcceleration * FrameRate::Get_Deltatime();
	//ジャンプ
	if (InputManager::getInstance()->GetKeyDown_SPACE() && canJump) {
		canJump = false;
		vel_y = -1.0f * PlayerJumpPower;
		jumpInputTime = GetNowHiPerformanceCount() / 1000000.0f;
	}
	if (!canJump) {
		//ジャンプボタンが離されたら
		if (InputManager::getInstance()->GetKeyUp_SPACE()) {
			if ((GetNowHiPerformanceCount() / 1000000.0f) - jumpInputTime < 0.1f) vel_y += 0.2f;
		}
	}
	_movementPerFrame.Set_y(_movementPerFrame.Get_y() + vel_y);

#if 0
	//移動制限
	if (Get_leftSide() + _movementPerFrame.Get_x() < 0.0f) _movementPerFrame.Set_x(-1 * Get_leftSide());
	if (Get_rightSide() + _movementPerFrame.Get_x() > (float)ScreenWidth) _movementPerFrame.Set_x((float)ScreenWidth - Get_rightSide());
	if (Get_bottomSide() + _movementPerFrame.Get_y() > (float)ScreenHeight) _movementPerFrame.Set_y((float)ScreenHeight - Get_bottomSide());
#endif
}

void Player::Draw() {
	DrawExtendGraph((int)Get_leftSide(), (int)Get_topSide(), (int)Get_rightSide(), (int)Get_bottomSide(), _gHandle, TRUE);
}