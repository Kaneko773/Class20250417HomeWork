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
	// 現在のシステム時間を取得
	nowTime = GetNowHiPerformanceCount();
	// 前回取得した時間からの経過時間を秒に変換してセット
	// ( GetNowHiPerformanceCount で取得できる値はマイクロ秒単位なので 1000000 で割ることで秒単位になる )
	deltaTime = (nowTime - time) / 1000000.0f;
	// 今回取得した時間を保存
	time = nowTime;
}

float FrameRateManager::Get_Deltatime() const {
	return deltaTime;
}