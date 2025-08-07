#include "DxLib.h"
#include "GameInfo.h"
#include "InputManager.h"
#include "FrameRateManager.h"

#include <time.h>//乱数
#include "Title.h"
#include "ScoreManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動
	ChangeWindowMode(TRUE);
	SetGraphMode(ScreenWidth, ScreenHeight, 16);
	// ScreenFlip を実行しても垂直同期信号を待たない
	SetWaitVSyncFlag(FALSE);
	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0) return -1;
	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	srand((unsigned int)time(NULL));//乱数初期化

	InputManager::create();
	ScoreManager::create();

	SequenceBase* currentScene = new Title();
	currentScene->Enter();

	while (ProcessMessage() == 0) {

		InputManager::getInstance()->Update_Key();

		ClearDrawScreen();//画面クリア

		SequenceBase* nextScene = currentScene->Execute();//更新
		currentScene->Draw();//描画
		if (nextScene != currentScene) //遷移
		{
			currentScene->Exit();
			delete currentScene;
			currentScene = nextScene;
			currentScene->Enter();
		}

		ScreenFlip();//表示

		FrameRateManager::getInstance()->FrameRateUpdate();//フレームレート更新

		//ゲーム終了(デバッグ)
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	if (currentScene) {
		currentScene->Exit();
		delete currentScene;
		currentScene = nullptr;
	}

	InputManager::destroy();
	ScoreManager::destroy();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}