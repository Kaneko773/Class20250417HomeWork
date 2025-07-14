#include "DxLib.h"
#include "GameInfo.h"
#include "Player.h"
#include "Paddle.h"
#include "FrameRate.h"
#include <list>
#include <time.h>
#include "HitJudgeManager.h"
#include <cmath>//atan

using namespace std;

//※
//実体化したパドルの降下スピードより、プレイヤーの降下速度が小さくならない様にする
// 
//プレイヤーの衝突応答が終わったらそれ以上の衝突判定はしなくて良いかも

//移動ベクトルを使って移動させる関数を作る（引数は移動の割合）

void PaddleListSort(list<Paddle>& list) {
	//パドルの数が１なら返す

	//パドルの移動後の高さでソート（移動前の高さでソートとどっちが良いかは分からない）//////////////////////////////
	//前から低いやつを後ろに回してく
}


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
	Player player(Vector2<float>(0.0f, (float)(ScreenHeight - PlayerPictureHeight / 2)));
	
	list<Paddle> paddles;
	PaddleListSort(paddles);
	Paddle firstPaddle(Vector2<float>(100, 100), Vector2<float>(100, 10));
	firstPaddle.SteppedOn();
	paddles.push_back(firstPaddle);

	HitJudgeManager::create();

	while (ProcessMessage() == 0) {
		ClearDrawScreen();//画面クリア

		//プレイヤーとパドルのUpdate
		player.Update();
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			(*i).Update();
		}

		
		float angle = atan2(player._movementPerFrame.Get_y(), player._movementPerFrame.Get_x()) * 180.0f / 3.14159265f;
		if (0 <= angle && angle <= 180)//プレイヤーの移動ベクトルが真横か下向きの時のみ判定///////////////////////////////////////////////////////////////////////////////
		{
			//パドルリストのソート
			PaddleListSort(paddles);

			//衝突判定と応答
			for (auto i = paddles.begin(); i != paddles.end(); ++i) {
				HitJudgeManager::getInstance()->ColliderUpdate(&player, &(*i));
			}
		}

		//衝突応答しなかったものを動かす
		if (!player._isCollisionResponse)player._center += player._movementPerFrame;
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			if (!(*i)._isCollisionResponse) (*i)._center += (*i)._movementPerFrame;
		}

		//パドルの範囲判定
		for (auto i = paddles.begin(); i != paddles.end();) {
			if (!(*i).RangeJudge()) {
				i = paddles.erase(i);
			}
			else {
				++i;
			}
		}


		//パドル生成
		//出てくる方向（左右）はランダム
		//要素の一番後ろに追加
		//プレイヤーがパドルに立っている時限定にした方が良いかも(canJumpがtrueの時)
		if (timer > nextPaddleCreateTime) {
#if 0
			int createPosY = (int)player.Get_topSide() - (rand() % 51 + 150);//生成する高さ プレイヤーの頭上150～200
			//生成
			int createPosX = (rand() % 2 == 0) ? -1 * (PaddleSizeWidth / 2) : ScreenWidth + (PaddleSizeWidth / 2);
			//Paddle paddle((float)createPosX, (float)createPosY, PaddleSizeWidth, PaddleSizeHeight);
			Paddle paddle(Vector2<float>((float)createPosX, (float)createPosY), Vector2<float>(PaddleSizeWidth, PaddleSizeHeight));
			paddles.push_back(paddle);
			//更新
			nextPaddleCreateTime += rand() % 3 + 4;/* - (rand() % 3 == 0 ? 3 : 0)*///３分の１で短スパンで出てくる
#endif
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
		//デバッグ//////////////////////
		DrawFormatString(0, 20, GetColor(255, 255, 255), "パドル数 : %d 個", paddles.size());
		DrawFormatString(0, 40, GetColor(255, 255, 255), "x : %f, y : %f", player._center.Get_x(), player._center.Get_y());
		player.Get_canJump() ? DrawFormatString(0, 60, GetColor(255, 255, 255), "true") : DrawFormatString(0, 60, GetColor(255, 255, 255), "false");
		DrawFormatString(0, 80, GetColor(255, 255, 255), "deltaTime : %f 秒", FrameRate::Get_Deltatime());
		DrawFormatString(0, 140, GetColor(255, 255, 255), "角度 : %f", atan2(player._movementPerFrame.Get_y(), player._movementPerFrame.Get_x()) * 180.0f / 3.14159265f);
		////////////////////////////////

		timer += FrameRate::Get_Deltatime();//時間更新

		FrameRate::FrameRateUpdate();//フレームレート更新

		ScreenFlip();//表示
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	for (auto i = paddles.begin(); i != paddles.end();) {
		i = paddles.erase(i);
	}

	HitJudgeManager::destroy();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}