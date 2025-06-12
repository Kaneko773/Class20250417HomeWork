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

	Vector2<float> size;
	size.Get_height() = PlayerPictureHeight / reductionMag;
	size.Get_width() = PlayerPictureWidth / reductionMag;

	Vector2<float> center;
	center.Get_x() = x;
	center.Get_y() = y;

	m_boxCollider.Initialization(center, size);

	canJump = false;
}
Player::~Player() {
	DeleteGraph(_gHandle);
}

bool Player::Update() {
	BoxCollider tempCollider = m_boxCollider;

	//左右移動
	if (CheckHitKey(KEY_INPUT_A) == 1) {//左
		tempCollider._center.Get_x() -= add * FrameRate::Get_Deltatime();
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {//右
		tempCollider._center.Get_x() += add * FrameRate::Get_Deltatime();
	}

	//テスト
	//重力
	vel += acc * FrameRate::Get_Deltatime() * 2;
	tempCollider._center.Get_y() += vel;
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

	//地面に着いたらゲームオーバー
	if (tempCollider.Get_bottomSide() >= ScreenHeight) {
		//return false;
		canJump = true;
	}

	//移動制限
	if (tempCollider.Get_leftSide() < 0) tempCollider._center.Get_x() = tempCollider._size.Get_width() / 2.0f;
	if (tempCollider.Get_rightSide() > ScreenWidth) tempCollider._center.Get_x() = ScreenWidth - (tempCollider._size.Get_width() / 2.0f);
	if (tempCollider.Get_topSide() < 0) tempCollider._center.Get_y() = tempCollider._size.Get_height() / 2.0f;
	if (tempCollider.Get_bottomSide() > ScreenHeight) tempCollider._center.Get_y() = ScreenHeight - (tempCollider._size.Get_height() / 2.0f);

	m_boxCollider._center = tempCollider._center;

	return true;
}

void Player::Draw() {
	DrawExtendGraph(m_boxCollider.Get_leftSide(), m_boxCollider.Get_topSide(), m_boxCollider.Get_rightSide(), m_boxCollider.Get_bottomSide(), _gHandle, TRUE);
}

float Player::Get_amountOfMovement() {
	return 0;
}