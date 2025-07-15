#include "Player.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRate.h"
#include "InputManager.h"

//ジャンプ
float jumpInputTime = 0;//ジャンプ入力がされた時間

float reductionMag = 4;//縮小倍率

Player::Player(Vector2<float> pos) {
	_gHandle = LoadGraph("画像/figure_jump.png");//358*400

	Vector2<float> size(PlayerPictureWidth / reductionMag, PlayerPictureHeight / reductionMag);

	_center = pos;
	_size = size;

	canJump = false;

	vel_y = 0;
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
		vel_y = -0.6f;
		jumpInputTime = GetNowHiPerformanceCount() / 1000000.0f;
	}
	if (!canJump) {
		//ジャンプボタンが離されたら
		if (InputManager::getInstance()->GetKeyUp_SPACE()) {
			if ((GetNowHiPerformanceCount() / 1000000.0f) - jumpInputTime < 0.1f) vel_y = (-0.15f);
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