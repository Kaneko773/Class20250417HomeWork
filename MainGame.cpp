#include "MainGame.h"
#include "DxLib.h"
#include "GameInfo.h"
#include "Player.h"
#include "Paddle.h"
#include "FrameRate.h"
#include <time.h>//����
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

	//����
	player = new Player(Vector2<float>(ScreenWidth / 2, ScreenHeight / 2 - 200.0f));
	Paddle* firstPaddle = new Paddle(Vector2<float>(ScreenWidth / 2, ScreenHeight / 2), Vector2<float>(100, 100));
	firstPaddle->SteppedOn();
	paddles.push_back(firstPaddle);

	//������
	HitJudgeManager::create();

	isMenu = false;
	menu_select = Menu_Select::BackGame;

	paddleFallSpeed = 1.0f;
}

bool MainGame::Menu() 
{
	//�I��
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

	//����
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

	//�Q�[������
	if (!isMenu) {
		//�v���C���[�ƃp�h����Update
		player->Update();
		paddleFallSpeed += PaddleAcceleration * FrameRate::Get_Deltatime();
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			(*i)->Update(paddleFallSpeed);
		}

		float angle = atan2(player->_movementPerFrame.Get_y(), player->_movementPerFrame.Get_x()) * 180.0f / 3.14159265f;
		if (0 <= angle && angle <= 180)
		{
			//�p�h�����X�g�̃\�[�g
			for (auto i = paddles.begin(); i != paddles.end(); ++i) {
				(*i)->Set_sort_y();//�\�[�g�p�ɒl��ݒ�
			}
			paddles.sort();

			//�Փ˔���Ɖ���
			for (auto i = paddles.begin(); i != paddles.end(); ++i) {
				HitJudgeManager::getInstance()->ColliderUpdate(player, *i);
			}
		}

		//�Փˉ������Ȃ��������̂𓮂���
		if (!player->_isCollisionResponse)player->_center += player->_movementPerFrame;
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			if (!(*i)->_isCollisionResponse) (*i)->_center += (*i)->_movementPerFrame;
		}

		//�p�h���͈͔̔���
		for (auto i = paddles.begin(); i != paddles.end();) {
			if (!(*i)->RangeJudge()) {
				i = paddles.erase(i);
			}
			else {
				++i;
			}
		}

		//�p�h������
		if (player->Get_canJump() && timer > nextPaddleCreateTime) {
			int createPosY = (int)player->Get_topSide() - (rand() % (Max_PaddleCreateHeight - Min_PaddleCreateHeight + 1) + Min_PaddleCreateHeight);//�������鍂�� �v���C���[�̓���100�`200
			//����
			int createPosX = (rand() % 2 == 0) ? -1 * (PaddleSizeWidth / 2) : ScreenWidth + (PaddleSizeWidth / 2);
			Paddle* paddle = new Paddle(Vector2<float>((float)createPosX, (float)createPosY), Vector2<float>(PaddleSizeWidth, PaddleSizeHeight));
			paddles.push_back(paddle);
			//�X�V
			nextPaddleCreateTime += rand() / 3 == 0 ? PaddleCreateCoolTime / 4.0f : PaddleCreateCoolTime;//�R���̂P�ŃN�[���^�C�����k��
		}

		//���j���[��ʂ��J��
		if (InputManager::getInstance()->GetKeyDown_M()) {
			isMenu = true;
		}
	}

	//���j���[
	if (isMenu) {
		if (!Menu()) {
			next = new Title();
		}
	}

	//���ԍX�V
	if(!isMenu) timer += FrameRate::Get_Deltatime();

	//�Q�[���I�[�o�[
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
	//�v���C���[
	player->Draw();
	//�p�h��
	for (auto i = paddles.begin(); i != paddles.end(); ++i) {
		(*i)->Draw();
	}
	//���̃g�Q�g�Q
	for (int i = 1; i <= 24; ++i) {
		DrawTriangle((int)((ScreenWidth / 24 * i) - ScreenWidth / 48), (int)(ScreenHeight - DeadZoneHeight), (int)(ScreenWidth / 24 * (i - 1)), (int)(ScreenHeight - 1), (int)(ScreenWidth / 24 * i), (int)(ScreenHeight - 1), GetColor(255, 255, 255), TRUE);
	}
	//�ӂ�΂�������
	DrawFormatString(30, 30, GetColor(255, 255, 255), "�ӂ�΂������� : %d �b", (int)timer);

	//���j���[���
	if (isMenu) {
		//�Q�[����ʂ𔼓����ɂ���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
		DrawBox(0, 0, ScreenWidth, ScreenHeight, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		//�I�����\��
		int DrawWidth3 = GetDrawStringWidth("�^�C�g����", -1);
		DrawString((ScreenWidth - DrawWidth3) / 2, ScreenHeight / 2 - 20, "�@������@", GetColor(255, 255, 255));
		DrawString((ScreenWidth - DrawWidth3) / 2, ScreenHeight / 2 + 20, "�^�C�g����", GetColor(255, 255, 255));
		switch (menu_select)
		{
		case Menu_Select::BackGame:
			DrawString((ScreenWidth - DrawWidth3) / 2 - 30, ScreenHeight / 2 - 20, "��", GetColor(255, 255, 255));
			break;
		case Menu_Select::GoTitle:
			DrawString((ScreenWidth - DrawWidth3) / 2 - 30, ScreenHeight / 2 + 20, "��", GetColor(255, 255, 255));
			break;
		}

		//��������\��
		int DrawWidth2 = GetDrawStringWidth("SPACE�Ō���", -1);
		DrawString((ScreenWidth - DrawWidth2) / 2, ScreenHeight / 4 * 3, "SPACE�Ō���", GetColor(255, 255, 255));
	}
}