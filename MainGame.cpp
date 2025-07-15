#include "MainGame.h"

#include "DxLib.h"
#include "GameInfo.h"
#include "Player.h"
#include "Paddle.h"
#include "FrameRate.h"
#include <time.h>
#include "HitJudgeManager.h"
#include <cmath>//atan
#include "InputManager.h"

using namespace std;

void MainGame::Enter()
{
	timer = 0.0f;
	nextPaddleCreateTime = (float)(rand() % 3 + 4);

	//����
	player = new Player(Vector2<float>(ScreenWidth / 2, ScreenHeight / 2 - 200.0f));
	Paddle* firstPaddle = new Paddle(Vector2<float>(ScreenWidth / 2, ScreenHeight / 2), Vector2<float>(100, 10));
	firstPaddle->SteppedOn();
	paddles.push_back(firstPaddle);

	//������
	HitJudgeManager::create();
}

SequenceBase* MainGame::Execute()
{
	SequenceBase* next = this;

	//�v���C���[�ƃp�h����Update
	player->Update();
	for (auto i = paddles.begin(); i != paddles.end(); ++i) {
		(*i)->Update();
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
	//�o�Ă�������i���E�j�̓����_��
	//�v�f�̈�Ԍ��ɒǉ�
	//�v���C���[���p�h���ɗ����Ă��鎞����ɂ��������ǂ�����(canJump��true�̎�)
	if (player->Get_canJump() && timer > nextPaddleCreateTime) {
		int createPosY = (int)player->Get_topSide() - (rand() % 51 + 150);//�������鍂�� �v���C���[�̓���150�`200
		//����
		int createPosX = (rand() % 2 == 0) ? -1 * (PaddleSizeWidth / 2) : ScreenWidth + (PaddleSizeWidth / 2);
		Paddle* paddle = new Paddle(Vector2<float>((float)createPosX, (float)createPosY), Vector2<float>(PaddleSizeWidth, PaddleSizeHeight));
		paddles.push_back(paddle);
		//�X�V
		nextPaddleCreateTime += rand() % 3 + 4;/* - (rand() % 3 == 0 ? 3 : 0)*///�R���̂P�ŒZ�X�p���ŏo�Ă���
	}

	//�`��
	player->Draw();
	for (auto i = paddles.begin(); i != paddles.end(); ++i) {
		(*i)->Draw();
	}
	unsigned int Cr = GetColor(255, 255, 255);
	//���̃g�Q�g�Q
	for (int i = 1; i <= 24; ++i) {
		DrawTriangle((int)((ScreenWidth / 24 * i) - ScreenWidth / 48), (int)(ScreenHeight - DeadZoneHeight), (int)(ScreenWidth / 24 * (i - 1)), (int)(ScreenHeight - 1), (int)(ScreenWidth / 24 * i), (int)(ScreenHeight - 1), Cr, TRUE);
	}
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�ӂ�΂������� : %d �b", (int)timer);

	//���ԍX�V
	timer += FrameRate::Get_Deltatime();

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
}