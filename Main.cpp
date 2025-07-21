#include "DxLib.h"
#include "GameInfo.h"
#include "InputManager.h"
#include "FrameRate.h"
#include <time.h>//乱数
#include "Title.h"
#include "MainGame.h"
#include "Result.h"
#include "ScoreManager.h"

//メニューを作るに当たって、現在時刻を取得する処理を工夫して
//パドルの出す間隔調整

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
	currentScene->Enter();

	while (ProcessMessage() == 0) {
		InputManager::getInstance()->FrameStart();

		ClearDrawScreen();//画面クリア

		SequenceBase* nextScene = currentScene->Execute(scoreManager);
		if (nextScene != currentScene) 
		{
			currentScene->Exit();
			delete currentScene;
			currentScene = nextScene;
			currentScene->Enter();
		}

		ScreenFlip();//表示

		FrameRate::FrameRateUpdate();//フレームレート更新
		InputManager::getInstance()->FrameEnd();

		//ゲーム終了(デバッグ)
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	if (currentScene) {
		currentScene->Exit();
		delete currentScene;
		currentScene = nullptr;
	}

	InputManager::destroy();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}