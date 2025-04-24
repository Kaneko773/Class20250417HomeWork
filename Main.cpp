#include "DxLib.h"
#include "Player.h"
//640�~480

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);
	// ScreenFlip �����s���Ă����������M����҂��Ȃ�
	SetWaitVSyncFlag(FALSE);
	// �c�w���C�u�����̏�����
	if (DxLib_Init() < 0) return -1;
	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	Player player(0, 0);
	bool a = true;

	while (ProcessMessage() == 0) {
		ClearDrawScreen();//��ʃN���A

		int tempx = player.Get_m_pos_x();
		if (a) {
			++tempx;
		}
		else {
			--tempx;
		}
		if (tempx > 640)a = false;
		if (tempx < 0)a = true;
		player.Set_m_pos(tempx, player.Get_m_pos_y());

		player.Draw();

		//���̃g�Q�g�Q
		unsigned int Cr = GetColor(255, 255, 255);
		for (int i = 1; i <= 10; ++i) {
			DrawTriangle((64 * i)-32, 400, 64 * (i-1), 479, 64 * i, 479, Cr, TRUE);
		}

		ScreenFlip();//�\��
		if (CheckHitKeyAll() != 0) break;
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}