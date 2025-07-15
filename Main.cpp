#include "DxLib.h"
#include "GameInfo.h"
#include "InputManager.h"
#include "FrameRate.h"
#include <time.h>//����
#include "MainGame.h"

//��
//���̉������p�h���̍~���X�s�[�h���A�v���C���[�̍~�����x���������Ȃ�Ȃ��l�ɂ���

//�f�o�b�O���[�h�����
//�f�o�b�O���[�h�I�����ɕύX��K�p����֐������

//��ʑJ�ڂ����

//���j���[�����ɓ������āA���ݎ������擾���鏈�����H�v����

//�p�h���̑��x�𗐐��ő�������

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

	srand((unsigned int)time(NULL));//����������

	InputManager::create();


	SequenceBase* currentScene = new MainGame();
	currentScene->Enter();

	while (ProcessMessage() == 0) {
		InputManager::getInstance()->FrameStart();

		ClearDrawScreen();//��ʃN���A

		SequenceBase* nextScene = currentScene->Execute();
		if (nextScene != currentScene) 
		{
			currentScene->Exit();
			delete currentScene;
			currentScene = nextScene;
		}

		ScreenFlip();//�\��

		FrameRate::FrameRateUpdate();//�t���[�����[�g�X�V
		InputManager::getInstance()->FrameEnd();

		//�Q�[���I��(�f�o�b�O)
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	InputManager::destroy();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}