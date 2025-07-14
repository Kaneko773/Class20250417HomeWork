#include "DxLib.h"
#include "GameInfo.h"
#include "Player.h"
#include "Paddle.h"
#include "FrameRate.h"
#include <list>
#include <time.h>
#include "HitJudgeManager.h"
#include <cmath>//atan

using namespace std;

//��
//���̉������p�h���̍~���X�s�[�h���A�v���C���[�̍~�����x���������Ȃ�Ȃ��l�ɂ���

//�f�o�b�O���[�h�����
//�f�o�b�O���[�h�I�����ɕύX��K�p����֐������

//��ʑJ�ڂ����

//���j���[�����ɓ������āA���ݎ������擾���鏈�����H�v����

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);
	SetGraphMode(ScreenWidth, ScreenHeight, 16);
	// ScreenFlip �����s���Ă����������M����҂��Ȃ�
	SetWaitVSyncFlag(FALSE);
	// �c�w���C�u�����̏�����
	if (DxLib_Init() < 0) return -1;
	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	float timer = 0.0f;
	srand((unsigned int)time(NULL));
	float nextPaddleCreateTime = (float)(rand() % 3 + 4);

	//����
	Player player(Vector2<float>(ScreenWidth / 2, ScreenHeight / 2));
	
	list<Paddle> paddles;
	Paddle firstPaddle(Vector2<float>(ScreenWidth / 2, ScreenHeight / 2), Vector2<float>(100, 10));
	firstPaddle.SteppedOn();
	paddles.push_back(firstPaddle);

	HitJudgeManager::create();

	while (ProcessMessage() == 0) {
		ClearDrawScreen();//��ʃN���A

		//�v���C���[�ƃp�h����Update
		player.Update();
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			(*i).Update();
		}

		float angle = atan2(player._movementPerFrame.Get_y(), player._movementPerFrame.Get_x()) * 180.0f / 3.14159265f;
		if (0 <= angle && angle <= 180)
		{
			//�p�h�����X�g�̃\�[�g
			for (auto i = paddles.begin(); i != paddles.end(); ++i) {
				(*i).Set_sort_y();//�\�[�g�p�ɒl��ݒ�
			}
			paddles.sort();

			//�Փ˔���Ɖ���
			for (auto i = paddles.begin(); i != paddles.end(); ++i) {
				HitJudgeManager::getInstance()->ColliderUpdate(&player, &(*i));
			}
		}

		//�Փˉ������Ȃ��������̂𓮂���
		if (!player._isCollisionResponse)player._center += player._movementPerFrame;
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			if (!(*i)._isCollisionResponse) (*i)._center += (*i)._movementPerFrame;
		}

		//�p�h���͈͔̔���
		for (auto i = paddles.begin(); i != paddles.end();) {
			if (!(*i).RangeJudge()) {
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
		if (player.Get_canJump() && timer > nextPaddleCreateTime) {
			int createPosY = (int)player.Get_topSide() - (rand() % 51 + 150);//�������鍂�� �v���C���[�̓���150�`200
			//����
			int createPosX = (rand() % 2 == 0) ? -1 * (PaddleSizeWidth / 2) : ScreenWidth + (PaddleSizeWidth / 2);
			Paddle paddle(Vector2<float>((float)createPosX, (float)createPosY), Vector2<float>(PaddleSizeWidth, PaddleSizeHeight));
			paddles.push_back(paddle);
			//�X�V
			nextPaddleCreateTime += rand() % 3 + 4;/* - (rand() % 3 == 0 ? 3 : 0)*///�R���̂P�ŒZ�X�p���ŏo�Ă���
		}


		//�`��
		player.Draw();
		for (auto i = paddles.begin(); i != paddles.end(); ++i) {
			(*i).Draw();
		}
		unsigned int Cr = GetColor(255, 255, 255);
		//���̃g�Q�g�Q
		for (int i = 1; i <= 24; ++i) {
			DrawTriangle((ScreenWidth / 24 * i) - ScreenWidth / 48, ScreenHeight - DeadZoneHeight, ScreenWidth / 24 * (i-1), ScreenHeight - 1, ScreenWidth / 24 * i, ScreenHeight - 1, Cr, TRUE);
		}
		DrawFormatString(0, 0, GetColor(255, 255, 255), "�ӂ�΂������� : %d �b", (int)timer);
#if 0
		//�f�o�b�O//////////////////////
		DrawFormatString(0, 20, GetColor(255, 255, 255), "�p�h���� : %d ��", paddles.size());
		DrawFormatString(0, 40, GetColor(255, 255, 255), "x : %f, y : %f", player._center.Get_x(), player._center.Get_y());
		player.Get_canJump() ? DrawFormatString(0, 60, GetColor(255, 255, 255), "true") : DrawFormatString(0, 60, GetColor(255, 255, 255), "false");
		DrawFormatString(0, 80, GetColor(255, 255, 255), "deltaTime : %f �b", FrameRate::Get_Deltatime());
		////////////////////////////////
#endif

		timer += FrameRate::Get_Deltatime();//���ԍX�V
		FrameRate::FrameRateUpdate();//�t���[�����[�g�X�V

		ScreenFlip();//�\��

		//�Q�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
		if (player.Get_bottomSide() > ScreenHeight - DeadZoneHeight) break;
	}

	for (auto i = paddles.begin(); i != paddles.end();) {
		i = paddles.erase(i);
	}

	HitJudgeManager::destroy();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}