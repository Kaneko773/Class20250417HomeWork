#include "Player.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRate.h"

// 速度を初期化( 1秒間に移動するドット数 )
float add = 200.0f;

//ジャンプ
bool canJump = true;//ジャンプ出来るかどうか
float jumpSpeed = 1.0f;                                                        //調整
float gravity = 300.0f / jumpSpeed;//重力( 1秒間に移動するドット数 )
float jumpingTime = 0;     // ジャンプの時間
const float MaxJumpTime = 1.0f;//ジャンプ出来る最大の時間　　　　            　//調整
float jumpTime = MaxJumpTime;//実際にジャンプ出来る時間
float jumpInputTime = 0;//ジャンプ入力がされた時間
const float smallJumpInput = 0.5f;//この値以下の時間の入力だと小ジャンプになる //調整
bool prevJumpInput = false;//前フレームのジャンプキーの入力

float reductionMag = 4;//縮小倍率

Player::Player(float x, float y) {
	_gHandle = LoadGraph("画像/figure_jump.png");//358*400

	Vector2<float> size;
	size.Get_height() = PlayerPictureHeight / reductionMag;
	size.Get_width() = PlayerPictureWidth / reductionMag;

	Vector2<float> center;
	center.Get_x() = x;
	center.Get_y() = y;

	m_boxCollider.Initialization(center, size);
}
Player::~Player() {
	DeleteGraph(_gHandle);
}

void Player::Update() {
	BoxCollider tempCollider = m_boxCollider;

	//左右移動
	if (CheckHitKey(KEY_INPUT_A) == 1) {//左
		tempCollider._center.Get_x() -= add * FrameRate::Get_Deltatime();
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {//右
		tempCollider._center.Get_x() += add * FrameRate::Get_Deltatime();
	}
	//重力
	tempCollider._center.Get_y() += gravity * FrameRate::Get_Deltatime() * (canJump ? 1.0f : jumpSpeed);
	//ジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && canJump) {
		canJump = false;
		jumpingTime = 0;
		prevJumpInput = true;
		jumpInputTime = GetNowHiPerformanceCount() / 1000000.0f;
	}
	if (!canJump) {
		//ジャンプボタンが離されたら
		if (!prevJumpInput) {
			if ((GetNowHiPerformanceCount() / 1000000.0f) - jumpInputTime < smallJumpInput) jumpTime = MaxJumpTime / 2;
		}

		if (jumpingTime < jumpTime) {
			tempCollider._center.Get_y() -= gravity * FrameRate::Get_Deltatime() * 2.0f * jumpSpeed;
		}

		prevJumpInput = CheckHitKey(KEY_INPUT_SPACE);

		//地面に着いたら再ジャンプ可能
		if (tempCollider.Get_bottomSide() >= ScreenHeight) {
			canJump = true;
			prevJumpInput = false;
			jumpTime = MaxJumpTime;
		}

		jumpingTime += FrameRate::Get_Deltatime();
	}

	//移動制限
	if (tempCollider.Get_leftSide() < 0) tempCollider._center.Get_x() = tempCollider._size.Get_width() / 2.0f;
	if (tempCollider.Get_rightSide() > ScreenWidth) tempCollider._center.Get_x() = ScreenWidth - (tempCollider._size.Get_width() / 2.0f);
	if (tempCollider.Get_topSide() < 0) tempCollider._center.Get_y() = tempCollider._size.Get_height() / 2.0f;
	if (tempCollider.Get_bottomSide() > ScreenHeight) tempCollider._center.Get_y() = ScreenHeight - (tempCollider._size.Get_height() / 2.0f);

	m_boxCollider._center = tempCollider._center;
}

void Player::Draw() {
	DrawExtendGraph(m_boxCollider.Get_leftSide(), m_boxCollider.Get_topSide(), m_boxCollider.Get_rightSide(), m_boxCollider.Get_bottomSide(), _gHandle, TRUE);
}