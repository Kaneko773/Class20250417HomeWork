#include "Player.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRate.h"

// 速度を初期化( 1秒間に移動するドット数 )
float add = 200.0f;

//ジャンプ
//テスト
float vel = 0; // y方向の速度
float acc = 1; // 重力加速度
bool prevJumpInput = false;//前フレームのジャンプキーの入力
float jumpInputTime = 0;//ジャンプ入力がされた時間

float reductionMag = 4;//縮小倍率

Player::Player(float x, float y) {
	_gHandle = LoadGraph("画像/figure_jump.png");//358*400

	Vector2<float> size(PlayerPictureWidth / reductionMag, PlayerPictureHeight / reductionMag);
	Vector2<float> center(x, y);

	_center = center;
	_size = size;

	canJump = false;
}
Player::~Player() {
	DeleteGraph(_gHandle);
}

bool Player::Update() {
	BoxCollider temp_collider;
	temp_collider._center = _center;
	temp_collider._size = _size;

	//左右移動
	if (CheckHitKey(KEY_INPUT_A) == 1) {//左
		temp_collider._center.Get_x() -= add * FrameRate::Get_Deltatime();
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {//右
		temp_collider._center.Get_x() += add * FrameRate::Get_Deltatime();
	}

	//テスト
	//重力
	vel += acc * FrameRate::Get_Deltatime() * 2;
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
	temp_collider._center.Get_y() += vel;

	//地面に着いたらゲームオーバー
	if (Get_bottomSide() >= (float)ScreenHeight) {
		//return false;
		canJump = true;
	}

	//移動制限
	if (temp_collider.Get_leftSide() < 0.0f) temp_collider._center.Get_x() = _size.Get_width() / 2.0f;
	if (temp_collider.Get_rightSide() > (float)ScreenWidth) temp_collider._center.Get_x() = (float)ScreenWidth - (_size.Get_width() / 2.0f);
	if (temp_collider.Get_topSide() < 0.0f) temp_collider._center.Get_y() = _size.Get_height() / 2.0f;
	if (temp_collider.Get_bottomSide() > (float)ScreenHeight) temp_collider._center.Get_y() = (float)ScreenHeight - (_size.Get_height() / 2.0f);

	_center = temp_collider._center;

	return true;
}

void Player::Draw() {
	DrawExtendGraph((int)Get_leftSide(), (int)Get_topSide(), (int)Get_rightSide(), (int)Get_bottomSide(), _gHandle, TRUE);
}

float Player::Get_amountOfMovement() {
	return 0;
}