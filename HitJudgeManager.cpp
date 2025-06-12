#include "HitJudgeManager.h"
#include "BoxCollider.h"
//#include "Player.h"
//#include "Paddle.h"

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

//bool HitJudgeManager::HitJudge(Player* player, Paddle* paddle)
bool HitJudgeManager::HitJudge(BoxCollider* playerCollider, BoxCollider* paddleCollider)
{
#if 1
	//bool HitJudgeManager::HitJudge(BoxCollider* playerCollider, BoxCollider* paddleCollider)
	//�v���C���[�̑̂̔����ȏオ�p�h��������ɂ��違�p�h������͂ݏo�Ă��Ȃ�
	if (playerCollider->_center.Get_y() < paddleCollider->Get_topSide()) {
		if (playerCollider->Get_rightSide() > paddleCollider->Get_leftSide() && playerCollider->Get_leftSide() < paddleCollider->Get_rightSide()) {
			//����̓p�h�����ђʂ��Ă��Ȃ���Γ�����������
			if (playerCollider->Get_bottomSide() > paddleCollider->Get_topSide() && playerCollider->Get_bottomSide() < paddleCollider->Get_bottomSide()) {
				return true;
			}
		}
	}
#endif



	return false;
}
