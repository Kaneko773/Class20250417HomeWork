#include "MainGame.h"

#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRateManager.h"
#include "InputManager.h"

#include "Player.h"
#include "HitJudgeManager.h"
#include "ScoreManager.h"
#include "Title.h"
#include "Result.h"
#include <time.h>//乱数
#include <cmath>//atan

MainGame::MainGame()
{
	player = nullptr;
	timer = 0;
	nextPaddleCreateTime = 0;
	isMenu = false;
	menuSelect = Menu_Select::BackGame;
	paddleFallSpeed = 0;
}
MainGame::~MainGame()
{
	if (player) {
		delete player;
		player = nullptr;
	}
	if (paddles.size() > 0) {
		paddles.clear();
	}
}

void MainGame::Enter()
{
	timer = 0.0f;
	nextPaddleCreateTime = PaddleCreateCoolTime;

	//生成
	player = new Player(Vector2{ ScreenWidth / 2, ScreenHeight / 2 - 200.0f }, { PlayerPictureWidth / ReductionMag, PlayerPictureHeight / ReductionMag });
	Paddle firstPaddle = { Vector2{ScreenWidth / 2, ScreenHeight / 2}, Vector2{100, 100} };
	firstPaddle.SteppedOn();
	paddles.push_back(firstPaddle);

	//初期化
	HitJudgeManager::create();

	isMenu = false;
	menuSelect = Menu_Select::BackGame;

	paddleFallSpeed = 1.0f;

	FrameRateManager::create();
}

bool MainGame::Menu() 
{
	//選択
	if (InputManager::getInstance()->key_down[KEY_INPUT_W]) {
		switch (menuSelect)
		{
		case Menu_Select::BackGame:
			menuSelect = Menu_Select::GoTitle;
			break;
		case Menu_Select::GoTitle:
			menuSelect = Menu_Select::BackGame;
			break;
		}
	}
	else if (InputManager::getInstance()->key_down[KEY_INPUT_S]) {
		switch (menuSelect)
		{
		case Menu_Select::BackGame:
			menuSelect = Menu_Select::GoTitle;
			break;
		case Menu_Select::GoTitle:
			menuSelect = Menu_Select::BackGame;
			break;
		}
	}

	//決定
	if (InputManager::getInstance()->key_down[KEY_INPUT_SPACE]) {
		switch (menuSelect)
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

	//メニュー画面を開いてる
	if (isMenu) 
	{
		if (!Menu()) 
		{
			next = new Title();
		}
	}
	//メニュー画面を開いてる
	else
	{
		//プレイヤーとパドルのUpdate
		player->Update();
		paddleFallSpeed += PaddleAcceleration * FrameRateManager::getInstance()->Get_Deltatime();
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			i->Update(paddleFallSpeed);
		}

		float angle = atan2(player->movementPerFrame.y, player->movementPerFrame.x) * 180.0f / 3.14159265f;
		if (0 <= angle && angle <= 180)
		{
			//パドルリストのソート
			for (auto i = paddles.begin(); i != paddles.end(); ++i) {
				i->Set_sort_y();//ソート用に値を設定
			}
			paddles.sort();

			//衝突判定と応答
			for (auto i = paddles.begin(); i != paddles.end(); ++i) {
				HitJudgeManager::getInstance()->ColliderUpdate(player, &(*i));
			}
		}

		//衝突応答しなかったものを動かす
		if (!player->isCollisionResponse) player->MoveByRate();
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			if (!i->isCollisionResponse) i->MoveByRate();
		}

		//パドルの範囲判定
		for (auto i = paddles.begin(); i != paddles.end();) {
			if (!i->RangeJudge()) {
				i = paddles.erase(i);
			}
			else {
				++i;
			}
		}

		//パドル生成
		if (player->Get_canJump() && timer > nextPaddleCreateTime) {
			int createPosY = (int)player->fourSides.topSide - (rand() % (Max_PaddleCreateHeight - Min_PaddleCreateHeight + 1) + Min_PaddleCreateHeight);//生成する高さ プレイヤーの頭上100～200
			//生成
			int createPosX = (rand() % 2 == 0) ? -1 * (PaddleSizeWidth / 2) : ScreenWidth + (PaddleSizeWidth / 2);
			Paddle paddle = { Vector2{(float)createPosX, (float)createPosY}, Vector2{PaddleSizeWidth, PaddleSizeHeight} };
			paddles.push_back(paddle);
			//更新
			nextPaddleCreateTime += rand() / 3 == 0 ? PaddleCreateCoolTime / 4.0f : PaddleCreateCoolTime;//３分の１でクールタイムが縮む
		}

		//メニュー画面を開く
		if (InputManager::getInstance()->key_down[KEY_INPUT_M]) {
			isMenu = true;
		}

		//ゲームオーバー
		if (player->fourSides.bottomSide > ScreenHeight - DeadZoneHeight) {
			next = new Result();
			ScoreManager::getInstance()->Set_prevGameScore((int)timer);//メニューからタイトルに戻るときは記録を取らないようにここで呼ぶ
		}

		timer += FrameRateManager::getInstance()->Get_Deltatime();
	}

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

	FrameRateManager::destroy();
}

void MainGame::Draw()
{
	//プレイヤー
	player->Draw();
	//パドル
	for (auto i = paddles.begin(); i != paddles.end(); ++i) {
		i->Draw();
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
		switch (menuSelect)
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