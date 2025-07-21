#include "Result.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "InputManager.h"
#include "Title.h"
#include "MainGame.h"

void Result::Enter()
{
	nextScene = ResultScene::NextScene::title;
}

SequenceBase* Result::Execute(ScoreManager& scoreManager)
{
	SequenceBase* next = this;

	//�ӂ�΂������ԕ\��
	int DrawWidth1 = GetDrawStringWidth("�ӂ�΂������� :     �b", -1);
	DrawFormatString((ScreenWidth - DrawWidth1) / 2, ScreenHeight / 4, GetColor(255, 255, 255), "�ӂ�΂������� : %d �b", scoreManager.Get_prevGameScore());

	//�I��
	if (InputManager::getInstance()->GetKeyDown_W()) {
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
	else if (InputManager::getInstance()->GetKeyDown_S()) {
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
	//�I�����\��
	int DrawWidth3 = GetDrawStringWidth("�^�C�g����", -1);
	DrawString((ScreenWidth - DrawWidth3) / 2, ScreenHeight / 2 - 20, "�^�C�g����", GetColor(255, 255, 255));
	DrawString((ScreenWidth - DrawWidth3) / 2, ScreenHeight / 2 + 20, "�@�Ē���@", GetColor(255, 255, 255));
	switch (nextScene)
	{
	case ResultScene::title:
		DrawString((ScreenWidth - DrawWidth3) / 2 - 30, ScreenHeight / 2 - 20, "��", GetColor(255, 255, 255));
		break;
	case ResultScene::mainGame:
		DrawString((ScreenWidth - DrawWidth3) / 2 - 30, ScreenHeight / 2 + 20, "��", GetColor(255, 255, 255));
		break;
	}

	//��������\��
	int DrawWidth2 = GetDrawStringWidth("SPACE�Ō���", -1);
	DrawString((ScreenWidth - DrawWidth2) / 2, ScreenHeight / 4 * 3, "SPACE�Ō���", GetColor(255, 255, 255));

	//����
	if (InputManager::getInstance()->GetKeyDown_SPACE()) {
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