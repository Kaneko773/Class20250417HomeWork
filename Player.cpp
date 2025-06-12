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

	//���E�ړ�
	if (CheckHitKey(KEY_INPUT_A) == 1) {//��
		tempCollider._center.Get_x() -= add * FrameRate::Get_Deltatime();
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {//�E
		tempCollider._center.Get_x() += add * FrameRate::Get_Deltatime();
	}

	//�e�X�g
	//�d��
	vel += acc * FrameRate::Get_Deltatime() * 2;
	tempCollider._center.Get_y() += vel;
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

	//�n�ʂɒ�������Q�[���I�[�o�[
	if (tempCollider.Get_bottomSide() >= ScreenHeight) {
		//return false;
		canJump = true;
	}

	//�ړ�����
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