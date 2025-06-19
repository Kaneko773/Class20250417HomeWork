#include "DxLib.h"
#include "GameInfo.h"
#include "Player.h"
#include "Paddle.h"
#include "FrameRate.h"
#include <list>
#include <time.h>
#include "HitJudgeManager.h"

//�p�h���͉�ʉ����畽�s�ړ����Ă���
//�v���C���[���������x�����̈ړ����~�܂��āA���ɗ�����

//�����蔻��ɂ���
//�v���C���[�̑O�t���[���̈ʒu�𒲂ׂ遨���̈ʒu�����ݒn������̎������Փˌ��o(�����Əォ�瓥�񂾎������Փˌ��o������)


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
	Player player(0.0f, (float)(ScreenHeight - PlayerPictureHeight / 2));
	
	std::list<Paddle> paddles;
	Paddle firstPaddle(100.0f, 100.0f, 100, 10);
	paddles.push_back(firstPaddle);

	HitJudgeManager::create();

	while (ProcessMessage() == 0) {
		ClearDrawScreen();//��ʃN���A

		if(!player.Update()) break;

		for (auto i = paddles.begin(); i != paddles.end();) {
			if (!(*i).Update()) {
				i = paddles.erase(i);
			}
			else {
				++i;
			}
		}

#if 0
		//�����蔻��
		for (int i = 0; i < paddles.size(); ++i) {
			if (HitJudgeManager::getInstance()->HitJudge(player.Test_Get_mboxCollider(), paddles[i].Test_Get_mboxCollider())) {
				paddles[i].SteppedOn();
			}
		}
#endif

		//�p�h������
		//�o�Ă�������i���E�j�̓����_��
		//�v�f�̈�Ԍ��ɒǉ�
		//�v���C���[���p�h���ɗ����Ă��鎞����ɂ��������ǂ�����/////////////////////////////////////////////////////////////////
		if (timer > nextPaddleCreateTime) {
			int createPosY = (int)player.Get_topSide() - (rand() % 51 + 150);//�������鍂�� �v���C���[�̓���150�`200
			//����
			int createPosX = (rand() % 2 == 0) ? -1 * (PaddleSizeWidth / 2) : ScreenWidth + (PaddleSizeWidth / 2);
			Paddle paddle((float)createPosX, (float)createPosY, PaddleSizeWidth, PaddleSizeHeight);
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
		for (int i = 1; i <= 10; ++i) {
			DrawTriangle((ScreenWidth / 10 * i)- ScreenWidth / 20, ScreenHeight - (ScreenWidth / 10), ScreenWidth / 10 * (i-1), ScreenHeight - 1, ScreenWidth / 10 * i, ScreenHeight - 1, Cr, TRUE);
		}//���̃g�Q�g�Q

		DrawFormatString(0, 0, GetColor(255, 255, 255), "�^�C�� : %d �b", (int)timer);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "�p�h���� : %d ��", paddles.size());//�f�o�b�O
		DrawFormatString(0, 40, GetColor(255, 255, 255), "x : %f, y : %f", player._center.Get_x(), player._center.Get_y());//�f�o�b�O
		player.Get_canJump() ? DrawFormatString(0, 60, GetColor(255, 255, 255), "true") : DrawFormatString(0, 60, GetColor(255, 255, 255), "false");
		timer += FrameRate::Get_Deltatime();

		FrameRate::FrameRateUpdate();//�t���[�����[�g�X�V

		ScreenFlip();//�\��
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	HitJudgeManager::destroy();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}