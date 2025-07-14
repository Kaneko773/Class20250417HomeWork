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
// 
//�v���C���[�̏Փˉ������I������炻��ȏ�̏Փ˔���͂��Ȃ��ėǂ�����

//�ړ��x�N�g�����g���Ĉړ�������֐������i�����͈ړ��̊����j

void PaddleListSort(list<Paddle>& list) {
	//�p�h���̐����P�Ȃ�Ԃ�

	//�p�h���̈ړ���̍����Ń\�[�g�i�ړ��O�̍����Ń\�[�g�Ƃǂ������ǂ����͕�����Ȃ��j//////////////////////////////
	//�O����Ⴂ������ɉ񂵂Ă�
}


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
	Player player(Vector2<float>(0.0f, (float)(ScreenHeight - PlayerPictureHeight / 2)));
	
	list<Paddle> paddles;
	PaddleListSort(paddles);
	Paddle firstPaddle(Vector2<float>(100, 100), Vector2<float>(100, 10));
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
		if (0 <= angle && angle <= 180)//�v���C���[�̈ړ��x�N�g�����^�����������̎��̂ݔ���///////////////////////////////////////////////////////////////////////////////
		{
			//�p�h�����X�g�̃\�[�g
			PaddleListSort(paddles);

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
		if (timer > nextPaddleCreateTime) {
#if 0
			int createPosY = (int)player.Get_topSide() - (rand() % 51 + 150);//�������鍂�� �v���C���[�̓���150�`200
			//����
			int createPosX = (rand() % 2 == 0) ? -1 * (PaddleSizeWidth / 2) : ScreenWidth + (PaddleSizeWidth / 2);
			//Paddle paddle((float)createPosX, (float)createPosY, PaddleSizeWidth, PaddleSizeHeight);
			Paddle paddle(Vector2<float>((float)createPosX, (float)createPosY), Vector2<float>(PaddleSizeWidth, PaddleSizeHeight));
			paddles.push_back(paddle);
			//�X�V
			nextPaddleCreateTime += rand() % 3 + 4;/* - (rand() % 3 == 0 ? 3 : 0)*///�R���̂P�ŒZ�X�p���ŏo�Ă���
#endif
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
		//�f�o�b�O//////////////////////
		DrawFormatString(0, 20, GetColor(255, 255, 255), "�p�h���� : %d ��", paddles.size());
		DrawFormatString(0, 40, GetColor(255, 255, 255), "x : %f, y : %f", player._center.Get_x(), player._center.Get_y());
		player.Get_canJump() ? DrawFormatString(0, 60, GetColor(255, 255, 255), "true") : DrawFormatString(0, 60, GetColor(255, 255, 255), "false");
		DrawFormatString(0, 80, GetColor(255, 255, 255), "deltaTime : %f �b", FrameRate::Get_Deltatime());
		DrawFormatString(0, 140, GetColor(255, 255, 255), "�p�x : %f", atan2(player._movementPerFrame.Get_y(), player._movementPerFrame.Get_x()) * 180.0f / 3.14159265f);
		////////////////////////////////

		timer += FrameRate::Get_Deltatime();//���ԍX�V

		FrameRate::FrameRateUpdate();//�t���[�����[�g�X�V

		ScreenFlip();//�\��
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	for (auto i = paddles.begin(); i != paddles.end();) {
		i = paddles.erase(i);
	}

	HitJudgeManager::destroy();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}