#include "DxLib.h"
#include "GameInfo.h"
#include "InputManager.h"
#include "Title.h"
#include "MainGame.h"

void Title::Enter()
{

}

SequenceBase* Title::Execute(ScoreManager& scoreManager)
{
	SequenceBase* next = this;

	DrawFormatString(0, 0, GetColor(255, 255, 255), "ハイスコア : %d 秒", scoreManager.Get_highScore());

	int DrawWidth = GetDrawStringWidth("SPACEを押してゲームスタート", -1);
	DrawString((ScreenWidth - DrawWidth) / 2, ScreenHeight / 2, "SPACEを押してゲームスタート", GetColor(255, 255, 255));

	if (InputManager::getInstance()->GetKeyDown_SPACE()) {
		next = new MainGame();
	}

	return next;
}

void Title::Exit()
{

}