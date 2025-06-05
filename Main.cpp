#include "DxLib.h"
#include "GameInfo.h"
#include "Player.h"
#include "Paddle.h"
#include "FrameRate.h"//
#include <vector>
#include <time.h>
//480×640

//パドルは画面横から平行移動してくる
//プレイヤーが乗ったらx方向の移動が止まって、下に落ちる

// プログラムは WinMain から始まります
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

	float timer = 0.0f;
	srand((unsigned int)time(NULL));
	float nextPaddleCreateTime = rand() % 3 + 4;

	//生成
	Player player(0.0f, (float)(ScreenHeight - PlayerPictureHeight / 2));
	
	std::vector<Paddle> paddles;
	Paddle firstPaddle(100.0f, 100.0f, 100, 10, paddles.size());
	paddles.push_back(firstPaddle);

	while (ProcessMessage() == 0) {
		ClearDrawScreen();//画面クリア

		player.Update();

		int prevPaddlesSize = paddles.size();
		for (int i = prevPaddlesSize; i > 0; --i) {
			if ( ! paddles[i - 1].Update()) {
				paddles.erase(paddles.begin() + paddles[i - 1].Get_m_arrayNum());
			}
		}
		//消えてるパドルがあったら全要素の添え字を変更
		if (paddles.size() != prevPaddlesSize) {
			for (int i = 0; i < paddles.size(); ++i) {
				paddles[i].Set_m_arrayNum(i);
			}
		}
		

		//当たり判定


		//パドル生成
		//出てくる方向（左右）はランダム
		//要素の一番後ろに追加
		//プレイヤーがパドルに立っている時限定にした方が良いかも/////////////////////////////////////////////////////////////////
		if (timer > nextPaddleCreateTime) {
			int createPosY = player.Get_m_boxCollider()._center.Get_y() - (rand() % 51 + 150);//生成する高さ プレイヤーの頭上150～200
			//生成
			int createPosX = (rand() % 2 == 0) ? -1 * (PaddleSizeWidth / 2) : ScreenWidth + (PaddleSizeWidth / 2);
			Paddle paddle(createPosX, createPosY, PaddleSizeWidth, PaddleSizeHeight, paddles.size());
			paddles.push_back(paddle);
			//更新
			nextPaddleCreateTime += rand() % 3 + 4;/* - (rand() % 3 == 0 ? 3 : 0)*///３分の１で短スパンで出てくる
		}

		//描画
		player.Draw();
		for (int i = 0; i < paddles.size(); ++i) {
			paddles[i].Draw();
		}
		unsigned int Cr = GetColor(255, 255, 255);
		for (int i = 1; i <= 10; ++i) {
			DrawTriangle((ScreenWidth / 10 * i)- ScreenWidth / 20, ScreenHeight - (ScreenWidth / 10), ScreenWidth / 10 * (i-1), ScreenHeight - 1, ScreenWidth / 10 * i, ScreenHeight - 1, Cr, TRUE);
		}//下のトゲトゲ

		DrawFormatString(0, 0, GetColor(255, 255, 255), "タイム : %d 秒", (int)timer);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "パドル数 : %d 個", paddles.size());//デバッグ
		timer += FrameRate::Get_Deltatime();

		FrameRate::FrameRateUpdate();//フレームレート更新

		ScreenFlip();//表示
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}