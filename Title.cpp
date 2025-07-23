#include "DxLib.h"
#include "GameInfo.h"
#include "InputManager.h"
#include "Title.h"
#include "MainGame.h"

void Title::Enter(ScoreManager& scoreManager)
{
	m_highScore = scoreManager.Get_highScore();
}

SequenceBase* Title::Execute()
{
	SequenceBase* next = this;

	if (InputManager::getInstance()->GetKeyDown_SPACE()) {
		next = new MainGame();
	}

	return next;
}

void Title::Exit(ScoreManager& scoreManager)
{

}

void Title::Draw() 
{
	DrawFormatString(30, 30, GetColor(255, 255, 255), "ハイスコア : %d 秒", m_highScore);

	int DrawWidth = GetDrawStringWidth("SPACEを押してゲームスタート", -1);
	DrawString((ScreenWidth - DrawWidth) / 2, ScreenHeight / 2, "SPACEを押してゲームスタート", GetColor(255, 255, 255));
}