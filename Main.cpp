#include "DxLib.h"
#include "GameInfo.h"
#include "InputManager.h"
#include "FrameRate.h"
#include <time.h>//����
#include "Title.h"
#include "MainGame.h"
#include "Result.h"
#include "ScoreManager.h"

//���j���[�����ɓ������āA���ݎ������擾���鏈�����H�v����
//�p�h���̏o���Ԋu����

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
	ScoreManager scoreManager;

	SequenceBase* currentScene = new Title();
	currentScene->Enter();

	while (ProcessMessage() == 0) {
		InputManager::getInstance()->FrameStart();

		ClearDrawScreen();//��ʃN���A

		SequenceBase* nextScene = currentScene->Execute(scoreManager);
		if (nextScene != currentScene) 
		{
			currentScene->Exit();
			delete currentScene;
			currentScene = nextScene;
			currentScene->Enter();
		}

		ScreenFlip();//�\��

		FrameRate::FrameRateUpdate();//�t���[�����[�g�X�V
		InputManager::getInstance()->FrameEnd();

		//�Q�[���I��(�f�o�b�O)
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	if (currentScene) {
		currentScene->Exit();
		delete currentScene;
		currentScene = nullptr;
	}

	InputManager::destroy();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}