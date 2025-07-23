#include "MainGame.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "Player.h"
#include "Paddle.h"
#include "FrameRate.h"
#include <time.h>//乱数
#include "HitJudgeManager.h"
#include <cmath>//atan
#include "InputManager.h"
#include "Result.h"
#include "Title.h"

using namespace std;

void MainGame::Enter(ScoreManager& scoreManager)
{
	timer = 0.0f;
	nextPaddleCreateTime = PaddleCreateCoolTime;

	//生成
	player = new Player(Vector2<float>(ScreenWidth / 2, ScreenHeight / 2 - 200.0f));
	Paddle* firstPaddle = new Paddle(Vector2<float>(ScreenWidth / 2, ScreenHeight / 2), Vector2<float>(100, 100));
	firstPaddle->SteppedOn();
	paddles.push_back(firstPaddle);

	//初期化
	HitJudgeManager::create();

	isMenu = false;
	menu_select = Menu_Select::BackGame;

	paddleFallSpeed = 1.0f;
}

bool MainGame::Menu() 
{
	//選択
	if (InputManager::getInstance()->GetKeyDown_W()) {
		switch (menu_select)
		{
		case Menu_Select::BackGame:
			menu_select = Menu_Select::GoTitle;
			break;
		case Menu_Select::GoTitle:
			menu_select = Menu_Select::BackGame;
			break;
		}
	}
	else if (InputManager::getInstance()->GetKeyDown_S()) {
		switch (menu_select)
		{
		case Menu_Select::BackGame:
			menu_select = Menu_Select::GoTitle;
			break;
		case Menu_Select::GoTitle:
			menu_select = Menu_Select::BackGame;
			break;
		}
	}

	//決定
	if (InputManager::getInstance()->GetKeyDown_SPACE()) {
		switch (menu_select)
		{
		case Menu_Select::BackGame:
			isMenu = false;
			break;
		case Menu_Select::GoTitle:
			return false;
			break;
		}
	}

	return true;
}

SequenceBase* MainGame::Execute()
{
	SequenceBase* next = this;

	//ゲーム処理
	if (!isMenu) {
		//プレイヤーとパドルのUpdate
		player->Update();
		paddleFallSpeed += PaddleAcceleration * FrameRate::Get_Deltatime();
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			(*i)->Update(paddleFallSpeed);
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
		if (player->Get_canJump() && timer > nextPaddleCreateTime) {
			int createPosY = (int)player->Get_topSide() - (rand() % (Max_PaddleCreateHeight - Min_PaddleCreateHeight + 1) + Min_PaddleCreateHeight);//生成する高さ プレイヤーの頭上100～200
			//生成
			int createPosX = (rand() % 2 == 0) ? -1 * (PaddleSizeWidth / 2) : ScreenWidth + (PaddleSizeWidth / 2);
			Paddle* paddle = new Paddle(Vector2<float>((float)createPosX, (float)createPosY), Vector2<float>(PaddleSizeWidth, PaddleSizeHeight));
			paddles.push_back(paddle);
			//更新
			nextPaddleCreateTime += rand() / 3 == 0 ? PaddleCreateCoolTime / 4.0f : PaddleCreateCoolTime;//３分の１でクールタイムが縮む
		}

		//メニュー画面を開く
		if (InputManager::getInstance()->GetKeyDown_M()) {
			isMenu = true;
		}
	}

	//メニュー
	if (isMenu) {
		if (!Menu()) {
			next = new Title();
		}
	}

	//時間更新
	if(!isMenu) timer += FrameRate::Get_Deltatime();

	//ゲームオーバー
	if (player->Get_bottomSide() > ScreenHeight - DeadZoneHeight) {
		next = new Result();
	}

	return next;
}

void MainGame::Exit(ScoreManager& scoreManager)
{
	HitJudgeManager::destroy();

	if (player != nullptr) {
		delete player;
		player = nullptr;
	}

	paddles.clear();

	scoreManager.Set_prevGameScore((int)timer);
}

void MainGame::Draw()
{
	//プレイヤー
	player->Draw();
	//パドル
	for (auto i = paddles.begin(); i != paddles.end(); ++i) {
		(*i)->Draw();
	}
	//下のトゲトゲ
	for (int i = 1; i <= 24; ++i) {
		DrawTriangle((int)((ScreenWidth / 24 * i) - ScreenWidth / 48), (int)(ScreenHeight - DeadZoneHeight), (int)(ScreenWidth / 24 * (i - 1)), (int)(ScreenHeight - 1), (int)(ScreenWidth / 24 * i), (int)(ScreenHeight - 1), GetColor(255, 255, 255), TRUE);
	}
	//ふんばった時間
	DrawFormatString(30, 30, GetColor(255, 255, 255), "ふんばった時間 : %d 秒", (int)timer);

	//メニュー画面
	if (isMenu) {
		//ゲーム画面を半透明にする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
		DrawBox(0, 0, ScreenWidth, ScreenHeight, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		//選択肢表示
		int DrawWidth3 = GetDrawStringWidth("タイトルへ", -1);
		DrawString((ScreenWidth - DrawWidth3) / 2, ScreenHeight / 2 - 20, "　続ける　", GetColor(255, 255, 255));
		DrawString((ScreenWidth - DrawWidth3) / 2, ScreenHeight / 2 + 20, "タイトルへ", GetColor(255, 255, 255));
		switch (menu_select)
		{
		case Menu_Select::BackGame:
			DrawString((ScreenWidth - DrawWidth3) / 2 - 30, ScreenHeight / 2 - 20, "→", GetColor(255, 255, 255));
			break;
		case Menu_Select::GoTitle:
			DrawString((ScreenWidth - DrawWidth3) / 2 - 30, ScreenHeight / 2 + 20, "→", GetColor(255, 255, 255));
			break;
		}

		//操作説明表示
		int DrawWidth2 = GetDrawStringWidth("SPACEで決定", -1);
		DrawString((ScreenWidth - DrawWidth2) / 2, ScreenHeight / 4 * 3, "SPACEで決定", GetColor(255, 255, 255));
	}
}