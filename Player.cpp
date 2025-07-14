#include "Player.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRate.h"

// 速度を初期化( 1秒間に移動するドット数 )
float add = 200.0f;

//ジャンプ
//テスト
float acc = 2; // 重力加速度
bool prevJumpInput = false;//前フレームのジャンプキーの入力
float jumpInputTime = 0;//ジャンプ入力がされた時間

float reductionMag = 4;//縮小倍率

Player::Player(Vector2<float> pos/*float x, float y*/) {
	_gHandle = LoadGraph("画像/figure_jump.png");//358*400

	Vector2<float> size(PlayerPictureWidth / reductionMag, PlayerPictureHeight / reductionMag);
	//Vector2<float> center(x, y);

	//_center = center;
	_center = pos;
	_size = size;

	canJump = false;

	vel = 0;
}
Player::~Player() {
	DeleteGraph(_gHandle);
}

void Player::Update() {

	_movementPerFrame.Reset();
	_isCollisionResponse = false;

	//左右移動
	if (CheckHitKey(KEY_INPUT_A) == 1) {//左
		//_movementPerFrame.Get_x() -= add * FrameRate::Get_Deltatime();
		_movementPerFrame.Set_x(_movementPerFrame.Get_x() - add * FrameRate::Get_Deltatime());
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {//右
		//_movementPerFrame.Get_x() += add * FrameRate::Get_Deltatime();
		_movementPerFrame.Set_x(_movementPerFrame.Get_x() + add * FrameRate::Get_Deltatime());
	}

	//テスト
	//重力
	vel += acc * FrameRate::Get_Deltatime();
	//ジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && canJump) {
		canJump = false;
		vel = -0.6f;
		jumpInputTime = GetNowHiPerformanceCount() / 1000000.0f;
	}
	if (!canJump) {
		//ジャンプボタンが離されたら
		if (!CheckHitKey(KEY_INPUT_SPACE)) {
			if ((GetNowHiPerformanceCount() / 1000000.0f) - jumpInputTime < 0.1f) vel = (-0.15f);
		}
	}
	//_movementPerFrame.Get_y() += vel;
	_movementPerFrame.Set_y(_movementPerFrame.Get_y() + vel);

	//地面に着いたらゲームオーバー
	if (Get_bottomSide() >= (float)ScreenHeight) {
		//return false;
		canJump = true;
	}

	//移動制限
	//if (Get_leftSide() + _movementPerFrame.Get_x() < 0.0f) _movementPerFrame.Get_x() = -1 * Get_leftSide();
	//if (Get_rightSide() + _movementPerFrame.Get_x() > (float)ScreenWidth) _movementPerFrame.Get_x() = (float)ScreenWidth - Get_rightSide();
	//if (Get_topSide() + _movementPerFrame.Get_y() < 0.0f) _movementPerFrame.Get_y() = -1 * Get_topSide();
	//if (Get_bottomSide() + _movementPerFrame.Get_y() > (float)ScreenHeight) _movementPerFrame.Get_y() = (float)ScreenHeight - Get_bottomSide();
	if (Get_leftSide() + _movementPerFrame.Get_x() < 0.0f) _movementPerFrame.Set_x(-1 * Get_leftSide());
	if (Get_rightSide() + _movementPerFrame.Get_x() > (float)ScreenWidth) _movementPerFrame.Set_x((float)ScreenWidth - Get_rightSide());
	if (Get_topSide() + _movementPerFrame.Get_y() < 0.0f) _movementPerFrame.Set_y(-1 * Get_topSide());
	if (Get_bottomSide() + _movementPerFrame.Get_y() > (float)ScreenHeight) _movementPerFrame.Set_y((float)ScreenHeight - Get_bottomSide());
}

void Player::Draw() {
	DrawExtendGraph((int)Get_leftSide(), (int)Get_topSide(), (int)Get_rightSide(), (int)Get_bottomSide(), _gHandle, TRUE);
}