#include "DxLib.h"
#include "GameInfo.h"
#include "InputManager.h"
#include "FrameRate.h"
#include <time.h>//乱数
#include "MainGame.h"

//※
//実体化したパドルの降下スピードより、プレイヤーの降下速度が小さくならない様にする

//デバッグモードを作る
//デバッグモード終了時に変更を適用する関数を作る

//画面遷移を作る

//メニューを作るに当たって、現在時刻を取得する処理を工夫して

//パドルの速度を乱数で早くする

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


	SequenceBase* currentScene = new MainGame();
	currentScene->Enter();

	while (ProcessMessage() == 0) {
		InputManager::getInstance()->FrameStart();

		ClearDrawScreen();//画面クリア

		SequenceBase* nextScene = currentScene->Execute();
		if (nextScene != currentScene) 
		{
			currentScene->Exit();
			delete currentScene;
			currentScene = nextScene;
		}

		ScreenFlip();//表示

		FrameRate::FrameRateUpdate();//フレームレート更新
		InputManager::getInstance()->FrameEnd();

		//ゲーム終了(デバッグ)
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	InputManager::destroy();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}