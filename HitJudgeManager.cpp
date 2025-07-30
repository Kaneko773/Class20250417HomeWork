#include "HitJudgeManager.h"
#include "BoxCollider.h"
#include "Player.h"
#include "Paddle.h"

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
	if (player->isCollisionResponse) return;//�v���C���[���Փˉ������Ă�����A���̃t���[���ł͂������肵�Ȃ�

	//���̉����Ă�
	if (paddle->Get_m_materialization())
	{
		paddle->MoveByRate();//�p�h���͐�ɓ�����
		if (HitJudge_materialization(player, paddle))
		{
			player->FixedMove({ player->center.x, paddle->fourSides.topSide - player->size.height / 2.0f });//�p�h���̏�ɗ���

			player->CanJump();
			player->vel_y = 0;
			player->isCollisionResponse = true;
			paddle->isCollisionResponse = true;
		}
	}
	//���̉����ĂȂ�
	else
	{
		float temp = HitJudge_notMaterialization(player, paddle);//�p�h���̈ړ��x�N�g����ŁA�v���C���[�Ɠ��������ꏊ�̊������Ԃ��Ă���(-1���Ɠ������ĂȂ�)
		if (temp != -1)
		{
			paddle->MoveByRate(temp);//���������Ƃ��܂ňړ�
			player->FixedMove({ player->center.x, paddle->fourSides.topSide - player->size.height / 2.0f });//�p�h���̏�ɗ���

			paddle->SteppedOn();//�p�h�������̉�

			player->CanJump();
			player->vel_y = 0;
			player->isCollisionResponse = true;
			paddle->isCollisionResponse = true;
		}
	}
}

float HitJudgeManager::Cross(const Vector2& vector1, const Vector2& vector2) const
{
	return vector1.x * vector2.y - vector1.y * vector2.x;
}
//�n���ꂽ�x�N�g�����m���������Ă邩�ǂ���
bool HitJudgeManager::IsCross(Vector2 startPoint1, Vector2 endPoint1, Vector2 startPoint2, Vector2 endPoint2) const
{
	Vector2 vector1 = endPoint1 - startPoint1;
	Vector2 vector2 = endPoint2 - startPoint2;

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
		{ player->fourSides.leftSide, player->fourSides.bottomSide },
		{ player->fourSides.leftSide + player->movementPerFrame.x, player->fourSides.bottomSide + player->movementPerFrame.y },
		{ paddle->fourSides.leftSide, paddle->fourSides.topSide },
		{ paddle->fourSides.rightSide, paddle->fourSides.topSide })
		)
		return true;
	//�v���C���[�̑���(�E��)
	if (IsCross(
		{ player->fourSides.rightSide, player->fourSides.bottomSide },
		{ player->fourSides.rightSide + player->movementPerFrame.x, player->fourSides.bottomSide + player->movementPerFrame.y },
		{ paddle->fourSides.leftSide, paddle->fourSides.topSide },
		{ paddle->fourSides.rightSide, paddle->fourSides.topSide })
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
			{ player->fourSides.leftSide, player->fourSides.bottomSide },
			{ player->fourSides.leftSide + player->movementPerFrame.x, player->fourSides.bottomSide + player->movementPerFrame.y },
			{ paddle->fourSides.leftSide + paddle->movementPerFrame.x * i, paddle->fourSides.topSide + paddle->movementPerFrame.y * i },
			{ paddle->fourSides.rightSide + paddle->movementPerFrame.x * i, paddle->fourSides.topSide + paddle->movementPerFrame.y * i })
			)
			return i;
	}
	//�v���C���[�̑���(�E��)�ƃp�h���̍���
	for (float i = 0; i <= 1.0f; i += 0.5f) {
		if (IsCross(
			{ player->fourSides.rightSide, player->fourSides.bottomSide },
			{ player->fourSides.rightSide + player->movementPerFrame.x, player->fourSides.bottomSide + player->movementPerFrame.y },
			{ paddle->fourSides.leftSide + paddle->movementPerFrame.x * i, paddle->fourSides.topSide + paddle->movementPerFrame.y * i },
			{ paddle->fourSides.rightSide + paddle->movementPerFrame.x * i, paddle->fourSides.topSide + paddle->movementPerFrame.y * i })
			)
			return i;
	}

	return -1;
}