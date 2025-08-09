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
#include <time.h>//����
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

	//����
	player = new Player(Vector2{ ScreenWidth / 2, ScreenHeight / 2 - 200.0f }, { PlayerPictureWidth / ReductionMag, PlayerPictureHeight / ReductionMag });
	Paddle firstPaddle = { Vector2{ScreenWidth / 2, ScreenHeight / 2}, Vector2{100, 100} };
	firstPaddle.SteppedOn();
	paddles.push_back(firstPaddle);

	//������
	HitJudgeManager::create();

	isMenu = false;
	menuSelect = Menu_Select::BackGame;

	paddleFallSpeed = 1.0f;

	FrameRateManager::create();
}

bool MainGame::Menu() 
{
	//�I��
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

	//����
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

	//���j���[��ʂ��J���Ă�
	if (isMenu) 
	{
		if (!Menu()) 
		{
			next = new Title();
		}
	}
	//���j���[��ʂ��J���Ă�
	else
	{
		//�v���C���[�ƃp�h����Update
		player->Update();
		paddleFallSpeed += PaddleAcceleration * FrameRateManager::getInstance()->Get_Deltatime();
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			i->Update(paddleFallSpeed);
		}

		float angle = atan2(player->movementPerFrame.y, player->movementPerFrame.x) * 180.0f / 3.14159265f;
		if (0 <= angle && angle <= 180)
		{
			//�p�h�����X�g�̃\�[�g
			for (auto i = paddles.begin(); i != paddles.end(); ++i) {
				i->Set_sort_y();//�\�[�g�p�ɒl��ݒ�
			}
			paddles.sort();

			//�Փ˔���Ɖ���
			for (auto i = paddles.begin(); i != paddles.end(); ++i) {
				HitJudgeManager::getInstance()->ColliderUpdate(player, &(*i));
			}
		}

		//�Փˉ������Ȃ��������̂𓮂���
		if (!player->isCollisionResponse) player->MoveByRate();
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			if (!i->isCollisionResponse) i->MoveByRate();
		}

		//�p�h���͈͔̔���
		for (auto i = paddles.begin(); i != paddles.end();) {
			if (!i->RangeJudge()) {
				i = paddles.erase(i);
			}
			else {
				++i;
			}
		}

		//�p�h������
		if (player->Get_canJump() && timer > nextPaddleCreateTime) {
			int createPosY = (int)player->fourSides.topSide - (rand() % (Max_PaddleCreateHeight - Min_PaddleCreateHeight + 1) + Min_PaddleCreateHeight);//�������鍂�� �v���C���[�̓���100�`200
			//����
			int createPosX = (rand() % 2 == 0) ? -1 * (PaddleSizeWidth / 2) : ScreenWidth + (PaddleSizeWidth / 2);
			Paddle paddle = { Vector2{(float)createPosX, (float)createPosY}, Vector2{PaddleSizeWidth, PaddleSizeHeight} };
			paddles.push_back(paddle);
			//�X�V
			nextPaddleCreateTime += rand() / 3 == 0 ? PaddleCreateCoolTime / 4.0f : PaddleCreateCoolTime;//�R���̂P�ŃN�[���^�C�����k��
		}

		//���j���[��ʂ��J��
		if (InputManager::getInstance()->key_down[KEY_INPUT_M]) {
			isMenu = true;
		}

		//�Q�[���I�[�o�[
		if (player->fourSides.bottomSide > ScreenHeight - DeadZoneHeight) {
			next = new Result();
			ScoreManager::getInstance()->Set_prevGameScore((int)timer);//���j���[����^�C�g���ɖ߂�Ƃ��͋L�^�����Ȃ��悤�ɂ����ŌĂ�
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
	//�v���C���[
	player->Draw();
	//�p�h��
	for (auto i = paddles.begin(); i != paddles.end(); ++i) {
		i->Draw();
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
		switch (menuSelect)
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