#include "Player.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRate.h"

// ���x��������( 1�b�ԂɈړ�����h�b�g�� )
float add = 200.0f;

//�W�����v
bool canJump = true;//�W�����v�o���邩�ǂ���
float jumpSpeed = 1.0f;                                                        //����
float gravity = 300.0f / jumpSpeed;//�d��( 1�b�ԂɈړ�����h�b�g�� )
float jumpingTime = 0;     // �W�����v�̎���
const float MaxJumpTime = 1.0f;//�W�����v�o����ő�̎��ԁ@�@�@�@            �@//����
float jumpTime = MaxJumpTime;//���ۂɃW�����v�o���鎞��
float jumpInputTime = 0;//�W�����v���͂����ꂽ����
const float smallJumpInput = 0.5f;//���̒l�ȉ��̎��Ԃ̓��͂��Ə��W�����v�ɂȂ� //����
bool prevJumpInput = false;//�O�t���[���̃W�����v�L�[�̓���

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
}
Player::~Player() {
	DeleteGraph(_gHandle);
}

void Player::Update() {
	BoxCollider tempCollider = m_boxCollider;

	//���E�ړ�
	if (CheckHitKey(KEY_INPUT_A) == 1) {//��
		tempCollider._center.Get_x() -= add * FrameRate::Get_Deltatime();
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {//�E
		tempCollider._center.Get_x() += add * FrameRate::Get_Deltatime();
	}
	//�d��
	tempCollider._center.Get_y() += gravity * FrameRate::Get_Deltatime() * (canJump ? 1.0f : jumpSpeed);
	//�W�����v
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && canJump) {
		canJump = false;
		jumpingTime = 0;
		prevJumpInput = true;
		jumpInputTime = GetNowHiPerformanceCount() / 1000000.0f;
	}
	if (!canJump) {
		//�W�����v�{�^���������ꂽ��
		if (!prevJumpInput) {
			if ((GetNowHiPerformanceCount() / 1000000.0f) - jumpInputTime < smallJumpInput) jumpTime = MaxJumpTime / 2;
		}

		if (jumpingTime < jumpTime) {
			tempCollider._center.Get_y() -= gravity * FrameRate::Get_Deltatime() * 2.0f * jumpSpeed;
		}

		prevJumpInput = CheckHitKey(KEY_INPUT_SPACE);

		//�n�ʂɒ�������ăW�����v�\
		if (tempCollider.Get_bottomSide() >= ScreenHeight) {
			canJump = true;
			prevJumpInput = false;
			jumpTime = MaxJumpTime;
		}

		jumpingTime += FrameRate::Get_Deltatime();
	}

	//�ړ�����
	if (tempCollider.Get_leftSide() < 0) tempCollider._center.Get_x() = tempCollider._size.Get_width() / 2.0f;
	if (tempCollider.Get_rightSide() > ScreenWidth) tempCollider._center.Get_x() = ScreenWidth - (tempCollider._size.Get_width() / 2.0f);
	if (tempCollider.Get_topSide() < 0) tempCollider._center.Get_y() = tempCollider._size.Get_height() / 2.0f;
	if (tempCollider.Get_bottomSide() > ScreenHeight) tempCollider._center.Get_y() = ScreenHeight - (tempCollider._size.Get_height() / 2.0f);

	m_boxCollider._center = tempCollider._center;
}

void Player::Draw() {
	DrawExtendGraph(m_boxCollider.Get_leftSide(), m_boxCollider.Get_topSide(), m_boxCollider.Get_rightSide(), m_boxCollider.Get_bottomSide(), _gHandle, TRUE);
}