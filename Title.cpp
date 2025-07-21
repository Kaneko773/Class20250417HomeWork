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

	DrawFormatString(0, 0, GetColor(255, 255, 255), "�n�C�X�R�A : %d �b", scoreManager.Get_highScore());

	int DrawWidth = GetDrawStringWidth("SPACE�������ăQ�[���X�^�[�g", -1);
	DrawString((ScreenWidth - DrawWidth) / 2, ScreenHeight / 2, "SPACE�������ăQ�[���X�^�[�g", GetColor(255, 255, 255));

	if (InputManager::getInstance()->GetKeyDown_SPACE()) {
		next = new MainGame();
	}

	return next;
}

void Title::Exit()
{

}