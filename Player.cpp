#include "Player.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRate.h"

// ���x��������( 1�b�ԂɈړ�����h�b�g�� )
float add = 200.0f;

//�W�����v
//�e�X�g
float vel = 0; // y�����̑��x
float acc = 1; // �d�͉����x
bool prevJumpInput = false;//�O�t���[���̃W�����v�L�[�̓���
float jumpInputTime = 0;//�W�����v���͂����ꂽ����

float reductionMag = 4;//�k���{��

Player::Player(float x, float y) {
	_gHandle = LoadGraph("�摜/figure_jump.png");//358*400

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

	//���E�ړ�
	if (CheckHitKey(KEY_INPUT_A) == 1) {//��
		temp_collider._center.Get_x() -= add * FrameRate::Get_Deltatime();
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {//�E
		temp_collider._center.Get_x() += add * FrameRate::Get_Deltatime();
	}

	//�e�X�g
	//�d��
	vel += acc * FrameRate::Get_Deltatime() * 2;
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
	temp_collider._center.Get_y() += vel;

	//�n�ʂɒ�������Q�[���I�[�o�[
	if (Get_bottomSide() >= (float)ScreenHeight) {
		//return false;
		canJump = true;
	}

	//�ړ�����
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