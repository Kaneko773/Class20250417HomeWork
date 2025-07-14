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
	if (player->_isCollisionResponse) return;//�v���C���[���Փˉ������Ă�����A���̃t���[���ł͂������肵�Ȃ�

	if (paddle->Get_m_materialization())
	{
		//���̉����Ă�
		if (HitJudge_materialization(player, paddle))
		{
			paddle->_center += paddle->_movementPerFrame;
			player->_center = { player->_center.Get_x(), paddle->Get_topSide() - player->_size.Get_height() / 2.0f };//�p�h���̏�ɗ���

			player->CanJump();
			player->vel = 0;
			player->_isCollisionResponse = true;
			paddle->_isCollisionResponse = true;
		}
	}
	else
	{
		//���̉����ĂȂ�
		float temp = HitJudge_notMaterialization(player, paddle);//�p�h���̈ړ��x�N�g����ŁA�v���C���[�Ɠ��������ꏊ�̊������Ԃ��Ă���(-1���Ɠ������ĂȂ�)
		if (temp != -1)
		{
			paddle->_center += paddle->_movementPerFrame * temp;//���������Ƃ��܂ňړ�
			player->_center = { player->_center.Get_x(), paddle->Get_topSide() - player->_size.Get_height() / 2.0f };//�p�h���̏�ɗ���

			paddle->SteppedOn();//�p�h�������̉�

			player->CanJump();
			player->vel = 0;
			player->_isCollisionResponse = true;
			paddle->_isCollisionResponse = true;
		}
	}
}

float Cross(Vector2<float> vector1, Vector2<float> vector2) {
	return vector1.Get_x() * vector2.Get_y() - vector1.Get_y() * vector2.Get_x();
}
//�n���ꂽ�x�N�g�����m���������Ă邩�ǂ���
bool IsCross(Vector2<float> startPoint1, Vector2<float> endPoint1, Vector2<float> startPoint2, Vector2<float> endPoint2) {

	Vector2<float> vector1 = endPoint1 - startPoint1;
	Vector2<float> vector2 = endPoint2 - startPoint2;

	if (Cross(vector1, startPoint2 - startPoint1) * Cross(vector1, endPoint2 - startPoint1) < 0 &&
		Cross(vector2, startPoint1 - startPoint2) * Cross(vector2, endPoint1 - startPoint2) < 0)
		return true;

	return false;
}
//���̉����Ă�p�h���Ƃ̔���
bool HitJudgeManager::HitJudge_materialization(BoxCollider* player, BoxCollider* paddle)
{
	//�v���C���[�̑���(����)
	if (IsCross(
		{ player->Get_leftSide(), player->Get_bottomSide() },
		{ player->Get_leftSide() + player->_movementPerFrame.Get_x(), player->Get_bottomSide() + player->_movementPerFrame.Get_y() },
		{ paddle->Get_leftSide(), paddle->Get_topSide() },
		{ paddle->Get_rightSide(), paddle->Get_topSide() })
		)
		return true;
	//�v���C���[�̑���(�E��)
	if (IsCross(
		{ player->Get_rightSide(), player->Get_bottomSide() },
		{ player->Get_rightSide() + player->_movementPerFrame.Get_x(), player->Get_bottomSide() + player->_movementPerFrame.Get_y() },
		{ paddle->Get_leftSide(), paddle->Get_topSide() },
		{ paddle->Get_rightSide(), paddle->Get_topSide() })
		)
		return true;

	return false;
}
//���̉����ĂȂ��p�h���Ƃ̔���
float HitJudgeManager::HitJudge_notMaterialization(BoxCollider* player, BoxCollider* paddle)
{
	//�v���C���[�̍��E�����i�Q�_�j����̈ړ��x�N�g���ƃp�h���̏�Ӂ@�i�ő�6�񔻒�j

	//�v���C���[�̑���(����)�ƃp�h���̏��
	for (float i = 0; i <= 1.0f; i += 0.5f) {
		if (IsCross(
			{ player->Get_leftSide(), player->Get_bottomSide() },
			{ player->Get_leftSide() + player->_movementPerFrame.Get_x(), player->Get_bottomSide() + player->_movementPerFrame.Get_y() },
			{ paddle->Get_leftSide() + paddle->_movementPerFrame.Get_x() * i, paddle->Get_topSide() + paddle->_movementPerFrame.Get_y() * i },
			{ paddle->Get_rightSide() + paddle->_movementPerFrame.Get_x() * i, paddle->Get_topSide() + paddle->_movementPerFrame.Get_y() * i })
			)
			return i;
	}
	//�v���C���[�̑���(�E��)�ƃp�h���̍���
	for (float i = 0; i <= 1.0f; i += 0.5f) {
		if (IsCross(
			{ player->Get_rightSide(), player->Get_bottomSide() },
			{ player->Get_rightSide() + player->_movementPerFrame.Get_x(), player->Get_bottomSide() + player->_movementPerFrame.Get_y() },
			{ paddle->Get_leftSide() + paddle->_movementPerFrame.Get_x() * i, paddle->Get_topSide() + paddle->_movementPerFrame.Get_y() * i },
			{ paddle->Get_rightSide() + paddle->_movementPerFrame.Get_x() * i, paddle->Get_topSide() + paddle->_movementPerFrame.Get_y() * i })
			)
			return i;
	}

	return -1;
}