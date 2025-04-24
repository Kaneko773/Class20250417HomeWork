#include "DxLib.h"
#include "Player.h"
//640×480

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動
	ChangeWindowMode(TRUE);
	// ScreenFlip を実行しても垂直同期信号を待たない
	SetWaitVSyncFlag(FALSE);
	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0) return -1;
	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	Player player(0, 0);
	bool a = true;

	while (ProcessMessage() == 0) {
		ClearDrawScreen();//画面クリア

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

		//下のトゲトゲ
		unsigned int Cr = GetColor(255, 255, 255);
		for (int i = 1; i <= 10; ++i) {
			DrawTriangle((64 * i)-32, 400, 64 * (i-1), 479, 64 * i, 479, Cr, TRUE);
		}

		ScreenFlip();//表示
		if (CheckHitKeyAll() != 0) break;
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}