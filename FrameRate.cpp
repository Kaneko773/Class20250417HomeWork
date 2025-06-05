#include "DxLib.h"
#include "FrameRate.h"

//可変フレームレート用
LONGLONG NowTime = GetNowHiPerformanceCount();
// システム時間を取得しておく
LONGLONG Time = GetNowHiPerformanceCount();
// 最初の経過時間は仮に 0.000001f 秒にしておく
float DeltaTime = 0.000001f;

void FrameRate::FrameRateUpdate()
{
	// 現在のシステム時間を取得
	NowTime = GetNowHiPerformanceCount();
	// 前回取得した時間からの経過時間を秒に変換してセット
	// ( GetNowHiPerformanceCount で取得できる値はマイクロ秒単位なので 1000000 で割ることで秒単位になる )
	DeltaTime = (NowTime - Time) / 1000000.0f;
	// 今回取得した時間を保存
	Time = NowTime;
}

float FrameRate::Get_Deltatime() {
	return DeltaTime;
}