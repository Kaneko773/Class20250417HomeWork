#include "DxLib.h"
#include "FrameRateManager.h"

FrameRateManager* FrameRateManager::pInstance = nullptr;
FrameRateManager::FrameRateManager()
{
	nowTime = GetNowHiPerformanceCount();
	time = GetNowHiPerformanceCount();
	deltaTime = 0.000001f;
}
FrameRateManager* FrameRateManager::getInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new FrameRateManager();
	}
	return pInstance;
}

void FrameRateManager::create()
{
	if (pInstance == nullptr)
	{
		pInstance = new FrameRateManager();
	}
}

void FrameRateManager::destroy()
{
	if (pInstance != nullptr)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}

void FrameRateManager::FrameRateUpdate()
{
	// ���݂̃V�X�e�����Ԃ��擾
	nowTime = GetNowHiPerformanceCount();
	// �O��擾�������Ԃ���̌o�ߎ��Ԃ�b�ɕϊ����ăZ�b�g
	// ( GetNowHiPerformanceCount �Ŏ擾�ł���l�̓}�C�N���b�P�ʂȂ̂� 1000000 �Ŋ��邱�Ƃŕb�P�ʂɂȂ� )
	deltaTime = (nowTime - time) / 1000000.0f;
	// ����擾�������Ԃ�ۑ�
	time = nowTime;
}

float FrameRateManager::Get_Deltatime() const {
	return deltaTime;
}