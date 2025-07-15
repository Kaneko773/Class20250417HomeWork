#include "MainGame.h"

#include "DxLib.h"
#include "GameInfo.h"
#include "Player.h"
#include "Paddle.h"
#include "FrameRate.h"
#include <time.h>
#include "HitJudgeManager.h"
#include <cmath>//atan
#include "InputManager.h"

using namespace std;

void MainGame::Enter()
{
	timer = 0.0f;
	nextPaddleCreateTime = (float)(rand() % 3 + 4);

	//生成
	player = new Player(Vector2<float>(ScreenWidth / 2, ScreenHeight / 2 - 200.0f));
	Paddle* firstPaddle = new Paddle(Vector2<float>(ScreenWidth / 2, ScreenHeight / 2), Vector2<float>(100, 10));
	firstPaddle->SteppedOn();
	paddles.push_back(firstPaddle);

	//初期化
	HitJudgeManager::create();
}

SequenceBase* MainGame::Execute()
{
	SequenceBase* next = this;

	//プレイヤーとパドルのUpdate
	player->Update();
	for (auto i = paddles.begin(); i != paddles.end(); ++i) {
		(*i)->Update();
	}

	float angle = atan2(player->_movementPerFrame.Get_y(), player->_movementPerFrame.Get_x()) * 180.0f / 3.14159265f;
	if (0 <= angle && angle <= 180)
	{
		//パドルリストのソート
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			(*i)->Set_sort_y();//ソート用に値を設定
		}
		paddles.sort();

		//衝突判定と応答
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			HitJudgeManager::getInstance()->ColliderUpdate(player, *i);
		}
	}

	//衝突応答しなかったものを動かす
	if (!player->_isCollisionResponse)player->_center += player->_movementPerFrame;
	for (auto i = paddles.begin(); i != paddles.end(); ++i) {
		if (!(*i)->_isCollisionResponse) (*i)->_center += (*i)->_movementPerFrame;
	}

	//パドルの範囲判定
	for (auto i = paddles.begin(); i != paddles.end();) {
		if (!(*i)->RangeJudge()) {
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
	if (player->Get_canJump() && timer > nextPaddleCreateTime) {
		int createPosY = (int)player->Get_topSide() - (rand() % 51 + 150);//生成する高さ プレイヤーの頭上150～200
		//生成
		int createPosX = (rand() % 2 == 0) ? -1 * (PaddleSizeWidth / 2) : ScreenWidth + (PaddleSizeWidth / 2);
		Paddle* paddle = new Paddle(Vector2<float>((float)createPosX, (float)createPosY), Vector2<float>(PaddleSizeWidth, PaddleSizeHeight));
		paddles.push_back(paddle);
		//更新
		nextPaddleCreateTime += rand() % 3 + 4;/* - (rand() % 3 == 0 ? 3 : 0)*///３分の１で短スパンで出てくる
	}

	//描画
	player->Draw();
	for (auto i = paddles.begin(); i != paddles.end(); ++i) {
		(*i)->Draw();
	}
	unsigned int Cr = GetColor(255, 255, 255);
	//下のトゲトゲ
	for (int i = 1; i <= 24; ++i) {
		DrawTriangle((int)((ScreenWidth / 24 * i) - ScreenWidth / 48), (int)(ScreenHeight - DeadZoneHeight), (int)(ScreenWidth / 24 * (i - 1)), (int)(ScreenHeight - 1), (int)(ScreenWidth / 24 * i), (int)(ScreenHeight - 1), Cr, TRUE);
	}
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ふんばった時間 : %d 秒", (int)timer);

	//時間更新
	timer += FrameRate::Get_Deltatime();

	return next;
}

void MainGame::Exit()
{
	HitJudgeManager::destroy();

	if (player != nullptr) {
		delete player;
		player = nullptr;
	}

	paddles.clear();
}