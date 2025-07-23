#include "Result.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "InputManager.h"
#include "Title.h"
#include "MainGame.h"

void Result::Enter(ScoreManager& scoreManager)
{
	m_nextScene = ResultScene::NextScene::title;

	m_enduredTime = scoreManager.Get_prevGameScore();
}

SequenceBase* Result::Execute()
{
	SequenceBase* next = this;

	//�I��
	if (InputManager::getInstance()->GetKeyDown_W()) {
		switch (m_nextScene)
		{
		case ResultScene::NextScene::title:
			m_nextScene = ResultScene::NextScene::mainGame;
			break;
		case ResultScene::NextScene::mainGame:
			m_nextScene = ResultScene::NextScene::title;
			break;
		}
	}
	else if (InputManager::getInstance()->GetKeyDown_S()) {
		switch (m_nextScene)
		{
		case ResultScene::NextScene::title:
			m_nextScene = ResultScene::NextScene::mainGame;
			break;
		case ResultScene::NextScene::mainGame:
			m_nextScene = ResultScene::NextScene::title;
			break;
		}
	}

	//����
	if (InputManager::getInstance()->GetKeyDown_SPACE()) {
		switch (m_nextScene)
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

void Result::Exit(ScoreManager& scoreManager)
{

}

void Result::Draw() 
{
	//�ӂ�΂������ԕ\��
	int DrawWidth1 = GetDrawStringWidth("�ӂ�΂������� :     �b", -1);
	DrawFormatString((ScreenWidth - DrawWidth1) / 2, ScreenHeight / 4, GetColor(255, 255, 255), "�ӂ�΂������� : %d �b", m_enduredTime);

	//�I�����\��
	int DrawWidth3 = GetDrawStringWidth("�^�C�g����", -1);
	DrawString((ScreenWidth - DrawWidth3) / 2, ScreenHeight / 2 - 20, "�^�C�g����", GetColor(255, 255, 255));
	DrawString((ScreenWidth - DrawWidth3) / 2, ScreenHeight / 2 + 20, "�@�Ē���@", GetColor(255, 255, 255));
	switch (m_nextScene)
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
}