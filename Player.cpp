#include "Player.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRate.h"

// ���x��������( 1�b�ԂɈړ�����h�b�g�� )
float add = 200.0f;

//�W�����v
//�e�X�g
float acc = 2; // �d�͉����x
bool prevJumpInput = false;//�O�t���[���̃W�����v�L�[�̓���
float jumpInputTime = 0;//�W�����v���͂����ꂽ����

float reductionMag = 4;//�k���{��

Player::Player(Vector2<float> pos/*float x, float y*/) {
	_gHandle = LoadGraph("�摜/figure_jump.png");//358*400

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

	//���E�ړ�
	if (CheckHitKey(KEY_INPUT_A) == 1) {//��
		//_movementPerFrame.Get_x() -= add * FrameRate::Get_Deltatime();
		_movementPerFrame.Set_x(_movementPerFrame.Get_x() - add * FrameRate::Get_Deltatime());
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {//�E
		//_movementPerFrame.Get_x() += add * FrameRate::Get_Deltatime();
		_movementPerFrame.Set_x(_movementPerFrame.Get_x() + add * FrameRate::Get_Deltatime());
	}

	//�e�X�g
	//�d��
	vel += acc * FrameRate::Get_Deltatime();
	//�W�����v
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && canJump) {
		canJump = false;
		vel = -0.6f;
		jumpInputTime = GetNowHiPerformanceCount() / 1000000.0f;
	}
	if (!canJump) {
		//�W�����v�{�^���������ꂽ��
		if (!CheckHitKey(KEY_INPUT_SPACE)) {
			if ((GetNowHiPerformanceCount() / 1000000.0f) - jumpInputTime < 0.1f) vel = (-0.15f);
		}
	}
	//_movementPerFrame.Get_y() += vel;
	_movementPerFrame.Set_y(_movementPerFrame.Get_y() + vel);

	//�n�ʂɒ�������Q�[���I�[�o�[
	if (Get_bottomSide() >= (float)ScreenHeight) {
		//return false;
		canJump = true;
	}

	//�ړ�����
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