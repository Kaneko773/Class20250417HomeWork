#include "HitJudgeManager.h"
#include "BoxCollider.h"
#include "Player.h"
#include "Paddle.h"

// �B��̃C���X�^���X
HitJudgeManager* HitJudgeManager::pInstance = nullptr;
HitJudgeManager* HitJudgeManager::getInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new HitJudgeManager();
	}
	return pInstance;
}

void HitJudgeManager::create()
{
	if (pInstance == nullptr)
	{
		pInstance = new HitJudgeManager();
	}
}

void HitJudgeManager::destroy()
{
	if (pInstance != nullptr)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}

void HitJudgeManager::ColliderUpdate(Player* player, Paddle* paddle)
{
	if (paddle->Get_m_materialization())
	{
#if 0
		IsCrossing(
			_lineSegment1.startPoint.position, _lineSegment1.endPoint.position,
			_lineSegment2.startPoint.position, _lineSegment2.endPoint.position
		)
#endif
		//���̉����Ă�
		if (HitJudge_materialization(player, paddle))
		{
			paddle->_center += paddle->_movementPerFrame;
			if (player->_movementPerFrame.Get_x() != 0) {

			}
			else {
				player->_center = { player->_center.Get_x(), paddle->Get_topSide() - player->_size.Get_height() / 2.0f };
			}

			player->CanJump();
			player->vel = 0;
			player->_isCollisionResponse = true;
			paddle->_isCollisionResponse = true;

			//���̉������p�h���͏Փˉ������ɂ��̂܂܉������āA���̏�Ƀv���C���[������

			//�p�h���̏�ɗ���(�Փˉ���)

			//�܂����ĂȂ�//////////////////////////////////////////////////////////////////////////////////
		}
	}
	else
	{
		//���̉����ĂȂ�
		if (HitJudge_notMaterialization(player, paddle))
		{
			//���̉����ĂȂ��p�h���ƃv���C���[�͓��������Ƃ��Ɉړ�����Ƀv���C���[�𗧂�����

			//�v���C���[�ƃp�h���𓖂������ʒu�Ɉړ��i�Փˉ����j
			//�p�h���͎��̉��A���������ʒu�Ɉړ�
			//�v���C���[�̓p�h���̏�ɗ�������A�����Ă锻��ɂ���
		}	
	}
}

float Cross(Vector2<float> vector1, Vector2<float> vector2) {
	return vector1.Get_x() * vector2.Get_y() - vector1.Get_y() * vector2.Get_x();
}
//���̉����Ă�p�h���Ƃ̔���
bool HitJudgeManager::HitJudge_materialization(BoxCollider* player, BoxCollider* paddle)
{
	//�v���C���[�̑���(����)
	Vector2<float> startPoint1 = { player->Get_leftSide(), player->Get_bottomSide() };//����
	Vector2<float> endPoint1 = {startPoint1.Get_x() + player->_movementPerFrame.Get_x(), startPoint1.Get_y() + player->_movementPerFrame.Get_y() };
	Vector2<float> startPoint2 = { paddle->Get_leftSide(), paddle->Get_topSide() };//�p�h���̏��
	Vector2<float> endPoint2 = { paddle->Get_rightSide(), paddle->Get_topSide() };

	// �x�N�g��P1Q1
	Vector2<float> vector1 = endPoint1 - startPoint1;
	// �x�N�g��P2Q2
	Vector2<float> vector2 = endPoint2 - startPoint2;
	//
	// �ȉ����������ׂĖ������Ƃ��������ƂȂ�
	//
	//    P1Q1 x P1P2 �� P1Q1 x P1Q2 ���ٕ���
	//                ����
	//    P2Q2 x P2P1 �� P2Q2 x P2Q1 ���ٕ���
	//
	if (Cross(vector1, startPoint2 - startPoint1) * Cross(vector1, endPoint2 - startPoint1) < 0 &&
		Cross(vector2, startPoint1 - startPoint2) * Cross(vector2, endPoint1 - startPoint2) < 0)
		return true;

	//�v���C���[�̑���(�E��)
	Vector2<float> startPoint3 = { player->Get_rightSide(), player->Get_bottomSide() };//����
	Vector2<float> endPoint3 = { startPoint3.Get_x() + player->_movementPerFrame.Get_x(), startPoint3.Get_y() + player->_movementPerFrame.Get_y() };
	Vector2<float> startPoint4 = { paddle->Get_leftSide(), paddle->Get_topSide() };//�p�h���̏��
	Vector2<float> endPoint4 = { paddle->Get_rightSide(), paddle->Get_topSide() };

	// �x�N�g��P1Q1
	Vector2<float> vector3 = endPoint3 - startPoint3;
	// �x�N�g��P2Q2
	Vector2<float> vector4 = endPoint4 - startPoint4;
	//
	// �ȉ����������ׂĖ������Ƃ��������ƂȂ�
	//
	//    P1Q1 x P1P2 �� P1Q1 x P1Q2 ���ٕ���
	//                ����
	//    P2Q2 x P2P1 �� P2Q2 x P2Q1 ���ٕ���
	//
	if (Cross(vector3, startPoint4 - startPoint3) * Cross(vector3, endPoint4 - startPoint3) < 0 &&
		Cross(vector4, startPoint3 - startPoint4) * Cross(vector4, endPoint3 - startPoint4) < 0)
		return true;

	//�v���C���[�̍��E�����i�Q�_�j����̈ړ��x�N�g���ƈړ���p�h���̏�ӂ��������Ă�Γ������Ă�

	return false;
}
//���̉����ĂȂ��p�h���Ƃ̔���
bool HitJudgeManager::HitJudge_notMaterialization(BoxCollider* player, BoxCollider* paddle)
{
	//�v���C���[�̍��E�����i�Q�_�j����̈ړ��x�N�g���ƃp�h���̏�ӂ̍��E�i�Q�_�j����̈ړ��x�N�g�����������Ă���Γ������Ă�@�i�ő�S�񔻒�j

	return false;
}