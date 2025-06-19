#include "DxLib.h"
#include "GameInfo.h"
#include "Player.h"
#include "Paddle.h"
#include "FrameRate.h"
#include <list>
#include <time.h>
#include "HitJudgeManager.h"

//パドルは画面横から平行移動してくる
//プレイヤーが乗ったらx方向の移動が止まって、下に落ちる

//当たり判定について
//プレイヤーの前フレームの位置を調べる→その位置が現在地よりも上の時だけ衝突検出(ちゃんと上から踏んだ時だけ衝突検出をする)


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
	float nextPaddleCreateTime = (float)(rand() % 3 + 4);

	//生成
	Player player(0.0f, (float)(ScreenHeight - PlayerPictureHeight / 2));
	
	std::list<Paddle> paddles;
	Paddle firstPaddle(100.0f, 100.0f, 100, 10);
	paddles.push_back(firstPaddle);

	HitJudgeManager::create();

	while (ProcessMessage() == 0) {
		ClearDrawScreen();//画面クリア

		if(!player.Update()) break;

		for (auto i = paddles.begin(); i != paddles.end();) {
			if (!(*i).Update()) {
				i = paddles.erase(i);
			}
			else {
				++i;
			}
		}

#if 0
		//当たり判定
		for (int i = 0; i < paddles.size(); ++i) {
			if (HitJudgeManager::getInstance()->HitJudge(player.Test_Get_mboxCollider(), paddles[i].Test_Get_mboxCollider())) {
				paddles[i].SteppedOn();
			}
		}
#endif

		//パドル生成
		//出てくる方向（左右）はランダム
		//要素の一番後ろに追加
		//プレイヤーがパドルに立っている時限定にした方が良いかも/////////////////////////////////////////////////////////////////
		if (timer > nextPaddleCreateTime) {
			int createPosY = (int)player.Get_topSide() - (rand() % 51 + 150);//生成する高さ プレイヤーの頭上150～200
			//生成
			int createPosX = (rand() % 2 == 0) ? -1 * (PaddleSizeWidth / 2) : ScreenWidth + (PaddleSizeWidth / 2);
			Paddle paddle((float)createPosX, (float)createPosY, PaddleSizeWidth, PaddleSizeHeight);
			paddles.push_back(paddle);
			//更新
			nextPaddleCreateTime += rand() % 3 + 4;/* - (rand() % 3 == 0 ? 3 : 0)*///３分の１で短スパンで出てくる
		}

		//描画
		player.Draw();
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			(*i).Draw();
		}
		unsigned int Cr = GetColor(255, 255, 255);
		for (int i = 1; i <= 10; ++i) {
			DrawTriangle((ScreenWidth / 10 * i)- ScreenWidth / 20, ScreenHeight - (ScreenWidth / 10), ScreenWidth / 10 * (i-1), ScreenHeight - 1, ScreenWidth / 10 * i, ScreenHeight - 1, Cr, TRUE);
		}//下のトゲトゲ

		DrawFormatString(0, 0, GetColor(255, 255, 255), "タイム : %d 秒", (int)timer);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "パドル数 : %d 個", paddles.size());//デバッグ
		DrawFormatString(0, 40, GetColor(255, 255, 255), "x : %f, y : %f", player._center.Get_x(), player._center.Get_y());//デバッグ
		player.Get_canJump() ? DrawFormatString(0, 60, GetColor(255, 255, 255), "true") : DrawFormatString(0, 60, GetColor(255, 255, 255), "false");
		timer += FrameRate::Get_Deltatime();

		FrameRate::FrameRateUpdate();//フレームレート更新

		ScreenFlip();//表示
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	HitJudgeManager::destroy();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}