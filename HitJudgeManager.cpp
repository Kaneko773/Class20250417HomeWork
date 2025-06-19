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

	

	//�����蔻��
	//�ړ���v���C���[�̒�ӂ��ړ���p�h���̏�ӈȉ��ɂ���
	//�G�ꂽ�p�h�������̉����Ă邩�ǂ���
	
	//���ĂȂ�
	//�@���݂��̍��ӉE�ӓ��m�̈ړ����ꎟ�֐��ɂ��Č�����Ă���X�ɔ���
	//�@�������Ă�����
	//�@�@�p�h�������̉�
	//�@�@�v���C���[��y�����̑��x��0�ɂ��遦�P�@�ꏏ
	//�@�@�p�h���̏�ӂɃv���C���[�̉��ӂ��ړ����P
	//�@�@�v���C���[�̓p�h���̏�ɗ����Ă锻��ɂ��遦�P
	//�@�������ĂȂ�������
	//�@�@��������

	//���Ă�
	//�@����Ă邩�ǂ����𒲂ׂ�
	//�@����Ă�����
	//�@�@�v���C���[��y�����̑��x��0�ɂ��遦�P
	//�@�@�p�h���̏�ӂɃv���C���[�̉��ӂ��ړ����P
	//�@�@�v���C���[�̓p�h���̏�ɗ����Ă锻��ɂ��遦�P
	//
	//�@����Ă��Ȃ�������
	//�@�@��������

	return false;
}
