#include "Result.h"

#include "DxLib.h"
#include "GameInfo.h"
#include "InputManager.h"

#include "Title.h"
#include "MainGame.h"
#include "ScoreManager.h"

Result::Result()
{
	nextScene = ResultScene::NextScene::title;
}
Result::~Result()
{

}

void Result::Enter()
{
	
}

SequenceBase* Result::Execute()
{
	SequenceBase* next = this;

	//選択
	if (InputManager::getInstance()->key_down[KEY_INPUT_W]) {
		switch (nextScene)
		{
		case ResultScene::NextScene::title:
			nextScene = ResultScene::NextScene::mainGame;
			break;
		case ResultScene::NextScene::mainGame:
			nextScene = ResultScene::NextScene::title;
			break;
		}
	}
	else if (InputManager::getInstance()->key_down[KEY_INPUT_S]) {
		switch (nextScene)
		{
		case ResultScene::NextScene::title:
			nextScene = ResultScene::NextScene::mainGame;
			break;
		case ResultScene::NextScene::mainGame:
			nextScene = ResultScene::NextScene::title;
			break;
		}
	}

	//決定
	if (InputManager::getInstance()->key_down[KEY_INPUT_SPACE]) {
		switch (nextScene)
		{
		case ResultScene::title:
			next = new Title();
			break;
		case ResultScene::mainGame:
			next = new MainGame();
			break;
		}
	}

	return next;
}

void Result::Exit()
{

}

void Result::Draw() 
{
	//ふんばった時間表示
	int DrawWidth1 = GetDrawStringWidth("ふんばった時間 :     秒", -1);
	DrawFormatString((ScreenWidth - DrawWidth1) / 2, ScreenHeight / 4, GetColor(255, 255, 255), "ふんばった時間 : %d 秒", ScoreManager::getInstance()->Get_prevGameScore());

	//選択肢表示
	int DrawWidth3 = GetDrawStringWidth("タイトルへ", -1);
	DrawString((ScreenWidth - DrawWidth3) / 2, ScreenHeight / 2 - 20, "タイトルへ", GetColor(255, 255, 255));
	DrawString((ScreenWidth - DrawWidth3) / 2, ScreenHeight / 2 + 20, "　再挑戦　", GetColor(255, 255, 255));
	switch (nextScene)
	{
	case ResultScene::title:
		DrawString((ScreenWidth - DrawWidth3) / 2 - 30, ScreenHeight / 2 - 20, "→", GetColor(255, 255, 255));
		break;
	case ResultScene::mainGame:
		DrawString((ScreenWidth - DrawWidth3) / 2 - 30, ScreenHeight / 2 + 20, "→", GetColor(255, 255, 255));
		break;
	}

	//操作説明表示
	int DrawWidth2 = GetDrawStringWidth("SPACEで決定", -1);
	DrawString((ScreenWidth - DrawWidth2) / 2, ScreenHeight / 4 * 3, "SPACEで決定", GetColor(255, 255, 255));
}