#include "DxLib.h"
#include "GameInfo.h"
#include "Player.h"
#include "Paddle.h"
#include "FrameRate.h"//
#include <vector>
#include <time.h>
//480�~640

//�p�h���͉�ʉ����畽�s�ړ����Ă���
//�v���C���[���������x�����̈ړ����~�܂��āA���ɗ�����

// �v���O������ WinMain ����n�܂�܂�
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
	float nextPaddleCreateTime = rand() % 3 + 4;

	//����
	Player player(0.0f, (float)(ScreenHeight - PlayerPictureHeight / 2));
	
	std::vector<Paddle> paddles;
	Paddle firstPaddle(100.0f, 100.0f, 100, 10, paddles.size());
	paddles.push_back(firstPaddle);

	while (ProcessMessage() == 0) {
		ClearDrawScreen();//��ʃN���A

		player.Update();

		int prevPaddlesSize = paddles.size();
		for (int i = prevPaddlesSize; i > 0; --i) {
			if ( ! paddles[i - 1].Update()) {
				paddles.erase(paddles.begin() + paddles[i - 1].Get_m_arrayNum());
			}
		}
		//�����Ă�p�h������������S�v�f�̓Y������ύX
		if (paddles.size() != prevPaddlesSize) {
			for (int i = 0; i < paddles.size(); ++i) {
				paddles[i].Set_m_arrayNum(i);
			}
		}
		

		//�����蔻��


		//�p�h������
		//�o�Ă�������i���E�j�̓����_��
		//�v�f�̈�Ԍ��ɒǉ�
		//�v���C���[���p�h���ɗ����Ă��鎞����ɂ��������ǂ�����/////////////////////////////////////////////////////////////////
		if (timer > nextPaddleCreateTime) {
			int createPosY = player.Get_m_boxCollider()._center.Get_y() - (rand() % 51 + 150);//�������鍂�� �v���C���[�̓���150�`200
			//����
			int createPosX = (rand() % 2 == 0) ? -1 * (PaddleSizeWidth / 2) : ScreenWidth + (PaddleSizeWidth / 2);
			Paddle paddle(createPosX, createPosY, PaddleSizeWidth, PaddleSizeHeight, paddles.size());
			paddles.push_back(paddle);
			//�X�V
			nextPaddleCreateTime += rand() % 3 + 4;/* - (rand() % 3 == 0 ? 3 : 0)*///�R���̂P�ŒZ�X�p���ŏo�Ă���
		}

		//�`��
		player.Draw();
		for (int i = 0; i < paddles.size(); ++i) {
			paddles[i].Draw();
		}
		unsigned int Cr = GetColor(255, 255, 255);
		for (int i = 1; i <= 10; ++i) {
			DrawTriangle((ScreenWidth / 10 * i)- ScreenWidth / 20, ScreenHeight - (ScreenWidth / 10), ScreenWidth / 10 * (i-1), ScreenHeight - 1, ScreenWidth / 10 * i, ScreenHeight - 1, Cr, TRUE);
		}//���̃g�Q�g�Q

		DrawFormatString(0, 0, GetColor(255, 255, 255), "�^�C�� : %d �b", (int)timer);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "�p�h���� : %d ��", paddles.size());//�f�o�b�O
		timer += FrameRate::Get_Deltatime();

		FrameRate::FrameRateUpdate();//�t���[�����[�g�X�V

		ScreenFlip();//�\��
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}