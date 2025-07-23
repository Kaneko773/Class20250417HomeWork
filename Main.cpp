#include "DxLib.h"
#include "GameInfo.h"
#include "InputManager.h"
#include "FrameRate.h"
#include <time.h>//乱数
#include "Title.h"
#include "MainGame.h"
#include "Result.h"
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
	ScoreManager scoreManager;

	SequenceBase* currentScene = new Title();
	currentScene->Enter(scoreManager);

	while (ProcessMessage() == 0) {
		InputManager::getInstance()->FrameStart();//入力更新

		ClearDrawScreen();//画面クリア

		SequenceBase* nextScene = currentScene->Execute();//更新
		currentScene->Draw();//描画
		if (nextScene != currentScene) //遷移
		{
			currentScene->Exit(scoreManager);
			delete currentScene;
			currentScene = nextScene;
			currentScene->Enter(scoreManager);
		}

		ScreenFlip();//表示

		FrameRate::FrameRateUpdate();//フレームレート更新
		InputManager::getInstance()->FrameEnd();//入力更新

		//ゲーム終了(デバッグ)
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	if (currentScene) {
		currentScene->Exit(scoreManager);
		delete currentScene;
		currentScene = nullptr;
	}

	InputManager::destroy();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}