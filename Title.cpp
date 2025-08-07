#include "Title.h"

#include "DxLib.h"
#include "GameInfo.h"
#include "InputManager.h"

#include "MainGame.h"
#include "ScoreManager.h"

Title::Title()
{
	
}
Title::~Title()
{
	
}

void Title::Enter()
{
	
}

SequenceBase* Title::Execute()
{
	SequenceBase* next = this;

	if (InputManager::getInstance()->key_down[KEY_INPUT_SPACE]) {
		next = new MainGame();
	}

	return next;
}

void Title::Exit()
{

}

void Title::Draw() 
{
	DrawFormatString(30, 30, GetColor(255, 255, 255), "�n�C�X�R�A : %d �b", ScoreManager::getInstance()->Get_highScore());

	int DrawWidth = GetDrawStringWidth("SPACE�������ăQ�[���X�^�[�g", -1);
	DrawString((ScreenWidth - DrawWidth) / 2, ScreenHeight / 2, "SPACE�������ăQ�[���X�^�[�g", GetColor(255, 255, 255));
}