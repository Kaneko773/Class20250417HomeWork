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
	DrawFormatString(30, 30, GetColor(255, 255, 255), "�n�C�X�R�A : %d �b", m_highScore);

	int DrawWidth = GetDrawStringWidth("SPACE�������ăQ�[���X�^�[�g", -1);
	DrawString((ScreenWidth - DrawWidth) / 2, ScreenHeight / 2, "SPACE�������ăQ�[���X�^�[�g", GetColor(255, 255, 255));
}